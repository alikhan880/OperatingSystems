import java.util.*;


class Counters{
	public static int dotsInCicle;
	public static int dotsInSquare;
}


class Randomization implements Runnable{
	Scanner sc = new Scanner(System.in);
	public void run(){
		System.out.println("How many dots to randomize?");
		Counters.dotsInSquare = sc.nextInt();
		Random rnd = new Random();
		for(int i=0; i<Counters.dotsInSquare; i++){
			double x = rnd.nextFloat();
			double y = rnd.nextFloat();
			double z = x * x + y * y;
			// System.out.println(z+'\n');
			if(z <= 1) Counters.dotsInCicle++;

		}
	}
}


public class MonteCarloPi{

	public static void main(String[] args){
		Randomization r = new Randomization();

		Thread thread = new Thread(r);
		thread.start();
		try{
			thread.join();
		}
		catch(InterruptedException e){
			 e.printStackTrace();
		}
		double respi = 4 * (double)Counters.dotsInCicle/(double)Counters.dotsInSquare;
		System.out.println(respi);

	}
}