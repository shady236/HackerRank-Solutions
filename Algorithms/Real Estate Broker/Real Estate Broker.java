import java.io.*;
import java.math.*;
import java.text.*;
import java.util.*;
import java.util.regex.*;

public class Solution {

    /*
     * Complete the realEstateBroker function below.
     */
    static int realEstateBroker(int[][] clients, int[][] houses) {
        /*
         * Write your code here.
         */
        List<List<Integer>> availableHouses = new ArrayList<>();
        for (int i = 0; i < clients.length; i++) {
            availableHouses.add(new ArrayList<>());
        }
        
        for (int i = 0; i < clients.length; i++) {
            int minArea = clients[i][0];
            int maxCost = clients[i][1];
            
            for (int j = 0; j < houses.length; j++) {
                int area = houses[j][0];
                int cost = houses[j][1];
                
                if (area >= minArea && cost <= maxCost) {
                    availableHouses.get(i).add(j);
                }
            }
        }
        
        int[] owner = new int[houses.length];
        Arrays.fill(owner, -1);
        
        for (int i = 0; i < clients.length; i++) {
            for (int h : availableHouses.get(i)) {
                freeHouse(availableHouses, owner, h);
                if (owner[h] == -1) {
                    owner[h] = i;
                    break;
                }
            }
        }
        
        int cnt = 0;
        for (int ownr : owner) {
            if (ownr != -1) {
                cnt++;
            }
        }
        return cnt;
    }
    
    private static void freeHouse(List<List<Integer>> availableHouses, int[] owner, int house) {
        boolean[] isVisited = new boolean[owner.length];
        freeHouse(availableHouses, owner, house, isVisited);
    }
    
    private static void freeHouse(List<List<Integer>> availableHouses, int[] owner, int house, boolean[] isVisited) {
        if (owner[house] == -1) {
            return;
        }
        
        isVisited[house] = true;
        int client = owner[house];
        for (int h : availableHouses.get(client)) {
            if (!isVisited[h]) {
                freeHouse(availableHouses, owner, h, isVisited);
                if (owner[h] == -1) {
                    owner[h] = client;
                    owner[house] = -1;
                    return;
                }
            }
        }
    }

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) throws IOException {
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        String[] nm = scanner.nextLine().split(" ");

        int n = Integer.parseInt(nm[0].trim());

        int m = Integer.parseInt(nm[1].trim());

        int[][] clients = new int[n][2];

        for (int clientsRowItr = 0; clientsRowItr < n; clientsRowItr++) {
            String[] clientsRowItems = scanner.nextLine().split(" ");

            for (int clientsColumnItr = 0; clientsColumnItr < 2; clientsColumnItr++) {
                int clientsItem = Integer.parseInt(clientsRowItems[clientsColumnItr].trim());
                clients[clientsRowItr][clientsColumnItr] = clientsItem;
            }
        }

        int[][] houses = new int[m][2];

        for (int housesRowItr = 0; housesRowItr < m; housesRowItr++) {
            String[] housesRowItems = scanner.nextLine().split(" ");

            for (int housesColumnItr = 0; housesColumnItr < 2; housesColumnItr++) {
                int housesItem = Integer.parseInt(housesRowItems[housesColumnItr].trim());
                houses[housesRowItr][housesColumnItr] = housesItem;
            }
        }

        int result = realEstateBroker(clients, houses);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedWriter.close();
    }
}
