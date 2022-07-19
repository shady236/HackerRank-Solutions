import java.io.*;
import java.util.*;

class Team
{
    public int startSkill;
    public int endSkill;
    
    public Team(int startSkill, int endSkill)
    {
        this.endSkill   = endSkill;
        this.startSkill = startSkill;
    }
}

public class Solution {
    
    public static int minTeamSize(List<Integer> members)
    {
        if(members.isEmpty())       return 0;
        
        Collections.sort(members);
        
        List<Team> teams = new ArrayList<Team>();
        
        for(int i=0; i<members.size(); i++)
        {
            int skil = members.get(i);
            
            //find min team size this member can join
            int joinTo = -1;
            for(int j=teams.size()-1; j>=0; j--)
            {
                if(skil == teams.get(j).endSkill + 1)
                {
                    if((joinTo == -1) || (teams.get(joinTo).endSkill - teams.get(joinTo).startSkill > teams.get(j).endSkill - teams.get(j).startSkill))
                        joinTo = j;
                }
                else if(skil > teams.get(j).endSkill)
                    break;
            }
            
            if(joinTo == -1)
                teams.add(new Team(members.get(i), members.get(i)));
            else
            {
                Team joinToTeam = teams.get(joinTo);
                joinToTeam.endSkill++;
                teams.set(joinTo, joinToTeam);
            }
        }
        
        // System.out.println("Debug");
        // for (int i = 0; i < teams.size(); i++) 
        //     System.out.println(teams.get(i).startSkill + " " + teams.get(i).endSkill);
        // System.out.println("end Debug");
        
        
        
        int minSize = members.size();
        
        for (int i = 0; i < teams.size(); i++) {
            int size = teams.get(i).endSkill - teams.get(i).startSkill + 1;
            if(minSize > size)
                minSize = size;
        }
        
        return minSize;
    }
    
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        
        int t = in.nextInt();
        for(int testCase=0; testCase<t; testCase++)
        {
            int n = in.nextInt();
            List<Integer> members = new ArrayList<>(n);
            for(int i=0; i<n; i++)
                members.add(in.nextInt());
            
            System.out.println(minTeamSize(members));
        }
        in.close();
    }
}
