package model;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Scanner;

import model.Player;
import model.Playground;
public class PlaygroundOwner extends Player implements Serializable {

    public void Role(HashMap<Integer, Playground> s)
    {
        Scanner in = new Scanner(System.in);
        while(true) {
            System.out.println("1- Resigt playground");
            System.out.println("2- back to main menu");
            System.out.print("Please enter your choice : ");
            int cho = in.nextInt();
            if(cho == 1)
            {
                in.nextLine();
                System.out.print("Please enter the name : ");
                String name1 = in.nextLine();
                System.out.print("Please enter the location : ");
                String location = in.nextLine();
                System.out.print("Please enter the Price Per Hour : ");
                int pricePerHour = in.nextInt();
                System.out.print("Please enter the size : ");
                Double size = in.nextDouble();
                Playground p = new Playground();
                p.setName(name1);
                p.setLocation(location);
                p.setPricePerHour(pricePerHour);
                p.setSize(size);
                s.put((int) p.getId(), p);
                System.out.print("Registering is succesful to back to main menu 4 or 0 to do another operation : ");
                int c1 = in.nextInt();
                if(c1==4)
                {break;
                }
                else
                    continue;
            }
            else if (cho==2)
                break;
            else
                continue;
        }
        //in.close();
        return;
    }
}
