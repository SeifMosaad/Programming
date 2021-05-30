package model;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Map.Entry;

public class Admin extends Player implements Serializable{

    public void Role(HashMap<Integer, Playground> s)
    {
        Scanner in = new Scanner(System.in);
        while(true) {
            System.out.println("1- To delete a playground");
            System.out.println("2- To suspend a playground");
            System.out.println("3- To active a playground");
            System.out.println("4- To back to main menu");
            System.out.print("Please enter your choice : ");
            int cho = in.nextInt();
            if(cho == 1)
            {
                for (Entry<Integer, Playground> mapElement : s.entrySet())
                {

                    System.out.println("Playground id ["+mapElement.getValue().getId()+"] "+mapElement.getValue().getName()+" "+mapElement.getValue().getLocation()+" "+mapElement.getValue().getPricePerHour()+" "+mapElement.getValue().getSize()+" "+mapElement.getValue().getStatus());
                }
                System.out.print("Please enter playground's id : ");
                int c = in.nextInt();
                if(deletePlayground(s, c))
                {System.out.print("The playground was successfully removed to back to main menu 4 or 0 to do another operation : ");}
                else {
                    System.out.print("The playground was unsuccessfully removed to back to main menu 4 or 0 to do another operation : ");
                }
                c = in.nextInt();
                if(c==4)
                    break;
                else if(c==0)
                    continue;
            }
            else if(cho==2)
            {
                for (Entry<Integer, Playground> mapElement : s.entrySet())
                {
                    System.out.println("Playground id ["+mapElement.getValue().getId()+"] "+mapElement.getValue().getName()+" "+mapElement.getValue().getLocation()+" "+mapElement.getValue().getPricePerHour()+" "+mapElement.getValue().getSize()+" "+mapElement.getValue().getStatus());
                }
                System.out.print("Please enter playground's id : ");
                int c = in.nextInt();
                if(suspendPlayground(s, c))
                {System.out.print("The playground was successfully suspended to back to main menu 4 or 0 to do another operation : ");}
                else {
                    System.out.print("The playground was unsuccessfully suspended to back to main menu 4 or 0 to do another operation : ");
                }
                c = in.nextInt();
                if(c==4)
                    break;
                else if(c==0)
                    continue;
            }
            else if(cho==3)
            {
                for (Entry<Integer, Playground> mapElement : s.entrySet())
                {
                    System.out.println("Playground id ["+mapElement.getValue().getId()+"] "+mapElement.getValue().getName()+" "+mapElement.getValue().getLocation()+" "+mapElement.getValue().getPricePerHour()+" "+mapElement.getValue().getSize()+" "+mapElement.getValue().getStatus());
                }
                System.out.print("Please enter playground's id : ");
                int c = in.nextInt();
                if(activePlayground(s, c))
                {System.out.print("The playground was successfully activated to back to main menu 4 or 0 to do another operation : ");}
                else {
                    System.out.print("The playground was unsuccessfully activated to back to main menu 4 or 0 to do another operation : ");
                }
                c = in.nextInt();
                if(c==4)
                    break;
                else if(c==0)
                    continue;
            }
            else if(cho==4)
            {
                break;
            }
            else {
                continue;
            }
        }
        return;
    }

    public boolean deletePlayground(HashMap<Integer, Playground> s , int id)
    {
        if(s.containsKey(id))
        {
            s.remove(id);
            return true;
        }
        else {
            return false;
        }
    }
    public boolean suspendPlayground(HashMap<Integer, Playground> s , int id)
    {
        if(s.containsKey(id))
        {
            s.get(id).setStatus(0);
            return true;
        }
        else {
            return false;
        }
    }
    public boolean activePlayground(HashMap<Integer, Playground> s , int id)
    {
        if(s.containsKey(id))
        {
            s.get(id).setStatus(2);
            return true;
        }
        else {
            return false;
        }
    }
}
