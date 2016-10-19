
import java.util.Scanner;
import java.io.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.ArrayList;

public class gift1 {

	public gift1() {
	}

	public static void main(String args[])
	{
		Scanner sc;
		PrintWriter wr;
		int NP;
		HashMap<String,Integer> map = new HashMap<String,Integer>();
		ArrayList<String> arr = new ArrayList<String>();
		try{
			sc = new Scanner(new File("gift1.in"));
		}
		catch(FileNotFoundException e)
		{
			System.out.println("File not found");
			return;
		}

		try{
			wr = new PrintWriter(new File("gift1.out"));
		}
		catch(IOException e)
		{
			System.out.println(e.getMessage());
			sc.close();
			return;
		}

		NP = sc.nextInt();
		for (int i = 0; i < NP; i++)
		{
			String name = sc.next();
			map.put(name,0);
			arr.add(name);
		}
		for (int i = 0; i < NP; i++)
		{
			String name = sc.next();
			int initMoney = sc.nextInt();
			int numGivers = sc.nextInt();
			if (numGivers == 0)
				continue;
			map.put(name, map.get(name) - initMoney + (initMoney % numGivers) );			
			for (int j = 0; j < numGivers; j++)
			{
				String giver = sc.next();
				map.put(giver, map.get(giver) + (initMoney / numGivers));
			}
		}
		for (int i = 0; i < NP; i++)
		{
			String member = arr.get(i);
			wr.println(member + " " + map.get(member));
		}
		wr.flush();
		sc.close();
		wr.close();
		System.exit(0);
	}

}
