public class Board {
    int array[];
    int p0Mancala = 6;
    int p1Mancala = 13;

    Board() {
        array = new int[14];
        for (int i = 0; i < 14; i++) {
            array[i] = 4;
        }
        array[p0Mancala] = 0;
        array[p1Mancala] = 0;
    }

    Board(Board board) {
        array = new int[14];
        for (int i = 0; i < 14; i++) {
            array[i] = board.getArray()[i];
        }
    }

    public int[] getArray() {
        return array;
    }

    public void setArray(int[] array) {
        this.array = array;
    }

    public int getP0Mancala() {
        return p0Mancala;
    }

    public int getP1Mancala() {
        return p1Mancala;
    }

    public void setP0Mancala(int p0Mancala) {
        this.p0Mancala = p0Mancala;
    }

    public void setP1Mancala(int p1Mancala) {
        this.p1Mancala = p1Mancala;
    }

    public boolean isValidMove(Agent agent, int slot_id) {
        if (agent.getTurn() == 0) {
            if (slot_id < 0 || slot_id > 5) {
                return false;
            }
        } else {
            if (slot_id < 7 || slot_id > 12) {
                return false;
            }
        }
        if (array[slot_id] == 0) {
            return false;
        }
        return true;
    }

    public boolean isGameOver() {
        boolean p0 = true;
        boolean p1 = true;
        for (int i = 0; i < 6; i++) {
            if (array[i] != 0) {
                p0 = false;
                break;
            }
        }
        for (int i = 7; i < 13; i++) {
            if (array[i] != 0) {
                p1 = false;
                break;
            }
        }
        return p0 || p1;
    }

    public boolean makeMove(Agent agent, int slot_id) {

        int stones = array[slot_id];
        array[slot_id] = 0;
        int i = slot_id + 1;
        while (stones > 0) {
            i=i%14;
            array[i]++;
            stones--;
            i++;
        }
        i--;
        i=i%14;
        if (agent.getTurn() == 0) {
            if (i == p0Mancala) {
                return true;
            }
        } else {
            if (i == p1Mancala) {
                return true;
            }
        }
        if (agent.getTurn() == 0) {
            if (array[i] == 1 && i>= 0 && i<= 5) {
                array[p0Mancala] += array[12-i] + 1;
                array[12-i] = 0;
                array[i] = 0;
            }
        } else {
            if (array[i] == 1 && i>= 7 && i<= 12) {
                array[p1Mancala] += array[12 - i] + 1;
                array[12 - i] = 0;
                array[i] = 0;
            }
        }
        return false;
    }

    public int getWinner() {
        if (array[p0Mancala] > array[p1Mancala]) {
            return 0;
        } else if (array[p0Mancala] < array[p1Mancala]) {
            return 1;
        } else {
            return -1;
        }
    }

    public int getP0Stone() {
        int sum = 0;
        for (int i = 0; i < 6; i++) {
            sum += array[i];
        }
        return sum;
    }

    public int getP1Stone() {
        int sum = 0;
        for (int i = 7; i < 13; i++) {
            sum += array[i];
        }
        return sum;
    }

    public int getCapturedStones() {
        return 48 - (array[p0Mancala] + array[p1Mancala]);
    }

    public void printBoard() {
        System.out.println("Player 1: ");
        for (int i = 12; i > 6; i--) {
            System.out.print(array[i] + " ");
        }
        System.out.println();
        System.out.println("Player 0: ");
        for (int i = 0; i < 6; i++) {
            System.out.print(array[i] + " ");
        }
        System.out.println();
        System.out.println("Player 0 Mancala: " + array[p0Mancala]);
        System.out.println("Player 1 Mancala: " + array[p1Mancala]);
    }

}
