public class BestInfo {
    private int bestVale;
    private int slot_id;
    private int free_turn;
    BestInfo(int bestVale, int slot_id, int free_turn){
        this.bestVale = bestVale;
        this.slot_id = slot_id;
        this.free_turn = free_turn;
    }
    BestInfo(BestInfo bestInfo){
        this.bestVale = bestInfo.getBestVale();
        this.slot_id = bestInfo.getSlot_id();
        this.free_turn = bestInfo.getFree_turn();
    }
    public int getBestVale() {
        return bestVale;
    }
    public int getSlot_id() {
        return slot_id;
    }
    public int getFree_turn() {
        return free_turn;
    }
    public void setBestVale(int bestVale) {
        this.bestVale = bestVale;
    }
    public void setSlot_id(int slot_id) {
        this.slot_id = slot_id;
    }
    public void setFree_turn(int free_turn) {
        this.free_turn = free_turn;
    }

    
}
