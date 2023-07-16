public class Agent {

    int depth;
    int heuristic;
    int turn;
    boolean isMaximizingPlayer;
    Agent opponent;

    int W1 = 5;
    int W2 = 10;
    int W3 = 11;
    int W4 = 9;

    Agent(int depth, int heuristic, int turn, boolean isMaximizingPlayer) {
        this.depth = depth;
        this.heuristic = heuristic;
        this.turn = turn;
        this.isMaximizingPlayer = isMaximizingPlayer;
    }

    Agent(Agent agent) {
        this.depth = agent.getDepth();
        this.heuristic = agent.getHeuristic();
        this.turn = agent.getTurn();
        this.isMaximizingPlayer = agent.getIsMaximizingPlayer();
    }

    public int getDepth() {
        return depth;
    }

    public int getHeuristic() {
        return heuristic;
    }

    public void setDepth(int depth) {
        this.depth = depth;
    }

    public void setHeuristic(int heuristic) {
        this.heuristic = heuristic;
    }

    public void setTurn(int turn) {
        this.turn = turn;
    }

    public void setMaximizingPlayer(boolean isMaximizingPlayer) {
        this.isMaximizingPlayer = isMaximizingPlayer;
    }

    public int getTurn() {
        return turn;
    }

    public boolean getIsMaximizingPlayer() {
        return isMaximizingPlayer;
    }

    public void setOpponent(Agent opponent) {
        this.opponent = opponent;
    }

    public Agent getOpponent() {
        return opponent;
    }

    public int getMove(Board board) {

        BestInfo best = Algorithm.minimax(board, this, opponent);

        if (!board.isValidMove(this, best.getSlot_id())) {
            System.out.println("Invalid Move from Agent" + best.getSlot_id());
            return -1;
        }
        return best.getSlot_id();
    }

    private int h1(Board board) {
        if (turn == 0) {
            return board.getP0Mancala() - board.getP1Mancala();
        } else {
            return board.getP1Mancala() - board.getP0Mancala();
        }
    }

    private int h2(Board board) {
        if (turn == 0) {

            int myStone = board.getP0Mancala();
            int oppStone = board.getP1Mancala();
            int myStoneInPit = board.getP0Stone();
            int oppStoneInPit = board.getP1Stone();
            int result = W1 * (myStone - oppStone) + W2 * (myStoneInPit - oppStoneInPit);
            return result;

        } else {
            int myStone = board.getP1Mancala();
            int oppStone = board.getP0Mancala();
            int myStoneInPit = board.getP1Stone();
            int oppStoneInPit = board.getP0Stone();
            int result = W1 * (myStone - oppStone) + W2 * (myStoneInPit - oppStoneInPit);
            return result;
        }
    }

    private int h3(Board board, int free_move) {
        if (turn == 0) {

            int myStone = board.getP0Mancala();
            int oppStone = board.getP1Mancala();
            int myStoneInPit = board.getP0Stone();
            int oppStoneInPit = board.getP1Stone();
            int result = W1 * (myStone - oppStone) + W2 * (myStoneInPit - oppStoneInPit) + W3 * free_move;
            return result;

        } else {
            int myStone = board.getP1Mancala();
            int oppStone = board.getP0Mancala();
            int myStoneInPit = board.getP1Stone();
            int oppStoneInPit = board.getP0Stone();
            int result = W1 * (myStone - oppStone) + W2 * (myStoneInPit - oppStoneInPit) + W3 * free_move;
            return result;
        }
    }

    private int h4(Board board, int free_move) {
        if (turn == 0) {

            int myStone = board.getP0Mancala();
            int oppStone = board.getP1Mancala();
            int myStoneInPit = board.getP0Stone();
            int oppStoneInPit = board.getP1Stone();
            int result = W1 * (myStone - oppStone) + W2 * (myStoneInPit - oppStoneInPit) + W3 * free_move
                    + W4 * myStone;
            return result;

        } else {
            int myStone = board.getP1Mancala();
            int oppStone = board.getP0Mancala();
            int myStoneInPit = board.getP1Stone();
            int oppStoneInPit = board.getP0Stone();
            int result = W1 * (myStone - oppStone) + W2 * (myStoneInPit - oppStoneInPit) + W3 * free_move
                    + W4 * myStone;
            return result;
        }
    }
    public int getHeuristicValue(Board board, int free_move) {
        if (heuristic == 1) {
            return h1(board);
        } else if (heuristic == 2) {
            return h2(board);
        } else if (heuristic == 3) {
            return h3(board, free_move);
        } else if (heuristic == 4) {
            return h4(board, free_move);
        } else {
            return -1;
        }
    }

}