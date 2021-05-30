package ui;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

import model.Admin;
import model.Player;
import model.Players;
import model.Playground;
import model.PlaygroundOwner;

public class Main {

    public static void main(String[] args) {
        HashMap<Integer, Playground>  playgrounds = new HashMap<Integer, Playground>();
        Players players = new Players();
        players.load();
        int cho;
        Scanner in1 = new Scanner(System.in);
        do {
            System.out.println("Welcome to GOFO Booking System");
            System.out.println("1- Login");
            System.out.println("2- Resigter");
            System.out.println("3- Exit");
            System.out.print("Please enter your choice : ");
            cho = in1.nextInt();
            if(cho == 1)
            {
                in1.nextLine();
                while(true)
                {
                    String un , pwd ;
                    System.out.println("Please enter your username : ");
                    un = in1.nextLine();
                    un.trim();
                    un = un.replaceAll("\\s","");
                    System.out.println("Please enter your password : ");
                    pwd = in1.nextLine();
                    int result =players.Login(un, pwd);
                    if(result==0)
                    {
                        int u ;
                        System.out.print("Username is not existed, to re-login press 1 or 0 to back to main menu : ");
                        u = in1.nextInt();
                        in1.nextLine();
                        if(u == 1)
                            continue;
                        else if(u == 0)
                            break;
                    }
                    else if(result==1)
                    {
                        int u ;
                        System.out.print("Username or Password is not correct, to re-login press 1 or 0 to back to main menu : ");
                        u = in1.nextInt();
                        in1.nextLine();
                        if(u == 1)
                            continue;
                        else if(u == 0)
                            break;
                    }
                    else {
                        System.out.println("Welcome , "+players.users.get(un).getName());
                        players.users.get(un).Role(playgrounds);
                        break;
                    }
                }
                continue;
            }
            else if(cho == 2)
            {
                in1.nextLine();
                System.out.print("Please enter your role [p/pg] : ");
                String c = in1.nextLine();
                c.toLowerCase();
                if(c.equals("p"))
                {
                    Player player = new Player();
                    if(players.Register(player))
                    {
                        System.out.println("Register was successful");
                        continue;
                    }
                    else
                    {
                        System.out.println("Register was unsuccessful");
                        continue;
                    }
                }
                else if(c.equals("pg"))
                {
                    Player playgroundOwner = new PlaygroundOwner();
                    if(players.Register(playgroundOwner))
                    {
                        System.out.println("Register was successful");
                        continue;
                    }
                    else
                    {
                        System.out.println("Register was unsuccessful");
                        continue;
                    }
                }
                else {
                    System.out.println("Wrong Choice");
                    continue;
                }
            }
            else if(cho==3)
            {
                players.save();
                break;
            }
        }while(cho !=3);
    }

}


