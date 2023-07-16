import java.util.Collections;
import java.util.Vector;

public class Algorithm {
    private static final int INF = 100000000;

    public static BestInfo minimax(Board board, Agent agent , Agent opponent) {
            if (agent.getDepth() == 0 || board.isGameOver()) {
                return new BestInfo(-INF, -1, 0);
            }
    
            if (agent.getIsMaximizingPlayer()) {

            BestInfo best = new BestInfo(-INF, -1, 0);

            Vector<Integer> moves = new Vector<>();
            for(int i=0;i<6;i++) moves.add(i);
            Collections.shuffle(moves);
            int[] boardArray= board.getArray();   


            for(int x=0;x<6;x++){
                int slot_id = moves.get(x);
                if(agent.getTurn() == 1)
                {
                    slot_id = slot_id + 6 + 1;
                }

                if(boardArray[slot_id] == 0) continue;

                if (board.isValidMove(agent, slot_id)) {

                    Board newBoard = new Board(board);
                    boolean free_turn=newBoard.makeMove(agent, slot_id);
                    Agent newAgent = new Agent(agent);
                    newAgent.setDepth(agent.getDepth() - 1);
                    BestInfo current = minimax(newBoard, opponent, newAgent);
                    current.setSlot_id(slot_id);
                    if (free_turn) {
                        current.setFree_turn(1);
                    }
                    else
                    current.setFree_turn(0);
                    current.setBestVale(agent.getHeuristic());
                    if (current.getBestVale() > best.getBestVale()) {
                        best = current;
                    }
                }
                
            }
            return best;
            }

            else {
                BestInfo best = new BestInfo(INF, -1, 0);
                Vector<Integer> moves = new Vector<>();
                for(int i=0;i<6;i++) moves.add(i);
                Collections.shuffle(moves);
                int[] boardArray= board.getArray();   
    
    
                for(int x=0;x<6;x++){
                    int slot_id = moves.get(x);
                    if(agent.getTurn() == 1)
                    {
                        slot_id = slot_id + 6 + 1;
                    }
    
                    if(boardArray[slot_id] == 0) continue;
    
                    if (board.isValidMove(agent, slot_id)) {
    
                        Board newBoard = new Board(board);
                        boolean free_turn=newBoard.makeMove(agent, slot_id);
                        Agent newAgent = new Agent(agent);
                        newAgent.setDepth(agent.getDepth() - 1);
                        BestInfo current = minimax(newBoard, opponent, newAgent);
                        current.setSlot_id(slot_id);
                        if(free_turn) current.setFree_turn(1);
                        else    
                        current.setFree_turn(0);
                        if (current.getBestVale() < best.getBestVale()) {
                            best = current;
                        }
    
                    }
                    
                }
                return best;
            }


    
}
}
