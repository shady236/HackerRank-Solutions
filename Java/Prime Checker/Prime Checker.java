

import static java.lang.System.in;

class Prime
{
    static boolean isPrime(int inputNumber)
    {
        if(inputNumber <= 1)        return false;
        
        for (int i = 2; i<= inputNumber/2; i++) 
            if((inputNumber % i) == 0)
                return false;
        
        return true;
    }
    
    
    void checkPrime(int... numbers)
    {
        for(int n : numbers)
        {
            if(isPrime(n))
                System.out.print(n + " ");
        }
        System.out.println();
    }
}


