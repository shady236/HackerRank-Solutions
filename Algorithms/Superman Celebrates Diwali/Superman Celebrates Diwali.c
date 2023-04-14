#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


#define  MAX_BUILDINGS_CNT       (1900)
#define  MAX_HEIGHT              (1900)


int max(int a, int b)
{
    if(a > b)
        return a;
    return b;
}


int supermanCelebratesDiwali(int buildings[MAX_BUILDINGS_CNT][MAX_HEIGHT], int buildingsCnt, int height, int jumpCost)
{
    /*
     * savedPeopleFromBuilding[i][h] stores maximum number of people that  
     * can be saved if superman starts from height h in building number i
     */
    int savedPeopleFromBuilding[MAX_BUILDINGS_CNT][MAX_HEIGHT] = {0};
    
    /*
     * savedPeople[h] stores maximum number of people that 
     * can be saved if superman starts from height h from any building
     */
    int savedPeople[MAX_HEIGHT] = {0};
    
    
    for (int h = 0; h < height; h++) 
    {
        for (int i = 0; i < buildingsCnt; i++) 
        {
            savedPeopleFromBuilding[i][h] = (
                buildings[i][h] +       // building number i is always the start
                savedPeopleFromBuilding[i][h - 1]       // no jump
            );
            
            if(h >= jumpCost)
            {
                int savedPeopleWithJump = (
                    buildings[i][h] +       // building number i is always the start
                    savedPeople[h - jumpCost]   // jump to building with most saved people
                );
                
                savedPeopleFromBuilding[i][h] = max(
                    savedPeopleFromBuilding[i][h],
                    savedPeopleWithJump
                );
            }
            
            savedPeople[h] = max(savedPeople[h], savedPeopleFromBuilding[i][h]);
        }
    }
    
    
    return savedPeople[height - 1];
}


int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    
    int buildingsCnt, height, jumpCost;
    scanf("%d %d %d", &buildingsCnt, &height, &jumpCost);
    
    /*
     * buildings[i][h] stores number of persons at height h in building number i
     */
    int buildings[MAX_BUILDINGS_CNT][MAX_HEIGHT] = {0};
    
    for(int i = 0; i < buildingsCnt; i++)
    {
        int totalPepoleCnt;
        scanf("%d", &totalPepoleCnt);
        
        for (int p = 0; p < totalPepoleCnt; p++) 
        {
            int floor;
            scanf("%d", &floor);
            floor--;
            buildings[i][floor]++;
        }
    }
    
    int res = supermanCelebratesDiwali(buildings, buildingsCnt, height, jumpCost);
    printf("%d\n", res);
    
    return 0;
}
