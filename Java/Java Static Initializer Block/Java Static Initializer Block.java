

private static Scanner scan = new Scanner(System.in);
private static int H = initH();
private static int B = initB();
private static boolean flag = initFlag();

private static int initH()
{
    return scan.nextInt();
}

private static int initB()
{
    int B = scan.nextInt();
    scan.close();
    return B;
}

private static boolean initFlag()
{
    if(B <= 0 || H <= 0)
    {
        System.out.println("java.lang.Exception: Breadth and height must be positive");
        return false;
    }
    return true;
}


