public class Main {

    public static void main(String[] args) {
        Board board = new Board();
        int turn = 0;
        Agent agent0 = new Agent(5,2,0,true);
        Agent agent1 = new Agent(5,2,1,false);
        agent0.setOpponent(agent1);
        agent1.setOpponent(agent0);
        while (!board.isGameOver()) {
            if (turn == 0) {
                int move=agent0.getMove(board);
                if(move == -1){
                    continue;
                }
                boolean freeTurn = board.makeMove(agent0,move);
                board.printBoard();
                if(freeTurn) continue;
                turn = 1;
            } else {

                int move=agent1.getMove(board);
                if(move == -1){
                    continue;
                }
                boolean freeTurn = board.makeMove(agent1,move);
                board.printBoard();
                if(freeTurn) continue;
                turn = 0;
            }
        }
        System.out.println("Game Over");
        board.printBoard();
        System.out.println("Player 0 Score: " + board.getArray()[board.getP0Mancala()]);
        System.out.println("Player 1 Score: " + board.getArray()[board.getP1Mancala()]);
        System.out.println("Winner: " + board.getWinner());
    }

}
