import java.util.*;

public class Solution {
    
    public static boolean canWin(int leap, int[] game, int idx, boolean[] isVisited) {
        
        if(idx + Math.max(leap, 1) >= game.length)
            return true;
        
        boolean res = false;
        
        if(game[idx + 1] == 0 && !isVisited[idx + 1]) {
            isVisited[idx + 1] = true;
            res = canWin(leap, game, idx + 1, isVisited);
            isVisited[idx + 1] = false;
            if(res)     return true;
        }
        
        
        if(game[idx + leap] == 0 && !isVisited[idx + leap]) {
            isVisited[idx + leap] = true;
            res = canWin(leap, game, idx + leap, isVisited);
            isVisited[idx + leap] = false;
            if(res)     return true;
        }
        
        if(idx > 0 && game[idx - 1] == 0 && !isVisited[idx - 1]) {
            isVisited[idx - 1] = true;
            res = canWin(leap, game, idx - 1, isVisited);
            isVisited[idx - 1] = false;
            if(res)     return true;
        }
        
        return res;
    }
    
    public static boolean canWin(int leap, int[] game) {
        // Return true if you can win the game; otherwise, return false.
        
        boolean[] isVisited = new boolean[game.length];
        for (int i = 0; i < game.length; i++) {
            isVisited[i] = false;
        }
        
        isVisited[0] = true;
        
        return canWin(leap, game, 0, isVisited);
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int q = scan.nextInt();
        while (q-- > 0) {
            int n = scan.nextInt();
            int leap = scan.nextInt();
            
            int[] game = new int[n];
            for (int i = 0; i < n; i++) {
                game[i] = scan.nextInt();
            }

            System.out.println( (canWin(leap, game)) ? "YES" : "NO" );
        }
        scan.close();
    }
}
