import java.util.*;
class Solution{
	
	public static void main(String []argh)
	{
		Scanner sc = new Scanner(System.in);
		
		while (sc.hasNext()) {
			String input=sc.next();
            //Complete the code
            Stack<Character> stack = new Stack<>();
            for(int i = 0; i<input.length(); i++)
            {
                if(stack.isEmpty())
                    stack.push(input.charAt(i));
                else 
                {
                    char top = stack.lastElement();
                    
                    switch(input.charAt(i))
                    {
                        case ')':
                            if(top == '(')
                                stack.pop();
                            else 
                                stack.push(input.charAt(i));
                        break;
                        
                        case '}':
                            if(top == '{')
                                stack.pop();
                            else 
                                stack.push(input.charAt(i));
                        break;
                        
                        case ']':
                            if(top == '[')
                                stack.pop();
                            else 
                                stack.push(input.charAt(i));
                        break;
                        
                        default:
                            stack.push(input.charAt(i));
                        break;
                    }
                }
            }
            
            System.out.println(stack.isEmpty());
		}
		
        sc.close();        
	}
}



