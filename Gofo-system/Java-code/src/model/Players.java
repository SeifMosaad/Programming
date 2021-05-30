package model;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.text.ParsePosition;
import java.text.SimpleDateFormat;
import java.util.HashMap;
import java.util.Scanner;

public class Players  implements Serializable{
    public HashMap<String, Player> users = new HashMap<String, Player>();
    public int ih = 1;
    public boolean Register(Player p)
    {
        Scanner in = new Scanner(System.in);
        String name ; String dob ; String address ; String mobile ; String email ; String username ; String password;
        p.id = this.ih;
        System.out.print("Please enter your name : ");
        name = in.nextLine();
        System.out.print("Please enter your dob : ");
        dob = in.nextLine();
        System.out.print("Please enter your address : ");
        address = in.nextLine();
        System.out.print("Please enter your mobile : ");
        mobile = in.nextLine();
        System.out.print("Please enter your email : ");
        email = in.nextLine();
        System.out.print("Please enter your username : ");
        username = in.nextLine();
        System.out.print("Please enter your password : ");
        password = in.nextLine();
        while(true)
        {
            if(name.isEmpty())
            {
                System.out.println("Name field can not be empty please re-enter it");
                System.out.print("Please enter your name : ");
                name = in.nextLine();
            }
            else if(dob.isEmpty() || !isDateValid(dob))
            {
                System.out.println("Date of birth field can not be empty, or wrong data form please re-enter it");
                System.out.print("Please enter your dob : ");
                dob = in.next();
                in.nextLine();
            }
            else if(address.isEmpty())
            {
                System.out.println("Address field can not be empty please re-enter it");
                System.out.print("Please enter your address : ");
                address = in.nextLine();

            }
            else if(!validatePhoneNumber(mobile))
            {
                System.out.println("mobile field can not be empty or mobile email form please re-enter it");
                System.out.print("Please enter your mobile : ");
                mobile = in.nextLine();
            }
            else if(!isValid(email))
            {
                System.out.println("Email field can not be empty or wronge email form please re-enter it");
                System.out.print("Please enter your email : ");
                email = in.nextLine();
            }
            else if(username.isEmpty())
            {

                System.out.println("Username field can not be empty please re-enter it");
                System.out.print("Please enter your username : ");
                username = in.nextLine();
            }
            else if(users.containsKey(username))
            {

                System.out.println("Username is taken please enter another one");
                System.out.print("Please enter your username : ");
                username = in.nextLine();
            }
            else if(password.isEmpty())
            {

                System.out.println("Username field can not be empty please re-enter it");
                System.out.print("Please enter your password : ");
                password = in.nextLine();
            }
            else {
                p.name = name;
                p.dob = dob;
                p.address=address;
                p.mobile=mobile;
                email.trim();
                email = email.replaceAll("\\s","");
                p.email=email;
                username.trim();
                username = username.replaceAll("\\s","");
                username.toLowerCase();
                p.username=username;
                p.password=password;
                this.ih++;
                users.put(p.username, p);
                //in.close();
                return true;
            }
        }
    }

    public int Login(String un , String pwd)
    {
        un.trim();
        un = un.replaceAll("\\s","");
        un.toLowerCase();
        int back = 0;
        if(!users.containsKey(un))
            return back;
        if(users.containsKey(un) && !users.get(un).password.equals(pwd))
            back = 1;
        if(users.containsKey(un) && users.get(un).password.equals(pwd))
        {
            back = 2;
        }

        return back;
    }

    public  boolean validatePhoneNumber(String phoneNo) {
        //validate phone numbers of format "1234567890"
        if (phoneNo.matches("\\d{10}")) return true;
            //validating phone number with -, . or spaces
        else if(phoneNo.matches("\\d{3}[-\\.\\s]\\d{3}[-\\.\\s]\\d{4}")) return true;
            //validating phone number with extension length from 3 to 5
        else if(phoneNo.matches("\\d{3}-\\d{3}-\\d{4}\\s(x|(ext))\\d{3,5}")) return true;
            //validating phone number where area code is in braces ()
        else if(phoneNo.matches("\\(\\d{3}\\)-\\d{3}-\\d{4}")) return true;
            //return false if nothing matches the input
        else return false;

    }
    public boolean isValid(String email) {
        email.trim();
        email = email.replaceAll("\\s","");
        String regex = "^[\\w-_\\.+]*[\\w-_\\.]\\@([\\w]+\\.)+[\\w]+[\\w]$";
        return email.matches(regex);
    }
    public void save ()
    {
        try
        {
            FileOutputStream fos =
                    new FileOutputStream("hashusers.txt");
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(users);
            oos.close();
            fos.close();
        }catch(IOException ioe)
        {
            ioe.printStackTrace();
        }
    }
    public void load()
    {
        try
        {
            FileInputStream fis = new FileInputStream("hashusers.txt");
            ObjectInputStream ois = new ObjectInputStream(fis);
            users = (HashMap) ois.readObject();
            ois.close();
            fis.close();
        }catch(IOException ioe)
        {
            Player adPlayer = new Admin();
            adPlayer.setId(-1);
            adPlayer.setName("admin");
            adPlayer.setDob("02-02-2020");
            adPlayer.setAddress("19-Admin");
            adPlayer.setMobile("1234567895");
            String emailS = "admin@gmail.com";
            emailS.trim();
            emailS = emailS.replaceAll("\\s",""); 
            adPlayer.setEmail(emailS);
            String usernameS = "admin";
            usernameS.trim();
            usernameS = usernameS.replaceAll("\\s",""); 
            adPlayer.setUsername(usernameS);
            adPlayer.setPassword("admin");
            users.put(adPlayer.username,adPlayer);
            return;
        }catch(ClassNotFoundException c)
        {
            System.out.println("Class not found");
            c.printStackTrace();
            return;
        }
    }
    public static boolean isDateValid(String s)
    {
        SimpleDateFormat sdf = new SimpleDateFormat("dd-MM-yyyy");
        sdf.setLenient(false);
        return sdf.parse(s, new ParsePosition(0)) != null;
    }
}
