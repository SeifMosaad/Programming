package model;

import java.io.Serializable;
import java.util.HashMap;
import java.util.List;
import java.util.Map.Entry;
import java.util.Scanner;

public class Player implements Serializable{
    protected int id;
    protected String name;
    protected String dob;
    protected String address;
    protected String mobile;
    protected String email;
    protected String username;
    protected String password;

    public Player()
    {
        this.id = 0;
        this.name="";
        this.dob = "";
        this.address="";
        this.mobile ="";
        this.email="";
        this.username="";
        this.password="";
    }
    public Player(int id , String name , String dob , String address , String mobile , String email , String username , String password)
    {
        this.id = id;
        this.name=name;
        this.dob = dob;
        this.address=address;
        this.mobile =mobile;
        this.email=email;
        this.username=username;
        this.password=password;
    }

    public int getId() {
        return id;
    }
    public void setId(int id) {
        this.id = id;
    }
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public String getDob() {
        return dob;
    }
    public void setDob(String dob) {
        this.dob = dob;
    }
    public String getAddress() {
        return address;
    }
    public void setAddress(String address) {
        this.address = address;
    }
    public String getMobile() {
        return mobile;
    }
    public void setMobile(String mobile) {
        this.mobile = mobile;
    }
    public String getEmail() {
        return email;
    }
    public void setEmail(String email) {
        this.email = email;
    }
    public String getUsername() {
        return username;
    }
    public void setUsername(String username) {
        this.username = username;
    }
    public String getPassword() {
        return password;
    }
    public void setPassword(String password) {
        this.password = password;
    }

    public void Role(HashMap<Integer, Playground> s)
    {
        Scanner in = new Scanner(System.in);
        if(s.isEmpty())
        {
        	System.out.println("There Aren't Any Playgrounds To Book");
        	return;
        }
        for (Entry<Integer, Playground> mapElement : s.entrySet())
        {
            if(mapElement.getValue().getStatus()==2)
            {System.out.println("Playground id ["+mapElement.getValue().getId()+"] "+mapElement.getValue().getName()+" "+mapElement.getValue().getLocation()+" "+mapElement.getValue().getPricePerHour()+" "+mapElement.getValue().getSize());}
        }
        System.out.print("Please enter playground's id : ");
        int c = in.nextInt();
        if(s.containsKey(c) && s.get(c).getStatus() == 2)
        {
            Date date;
            int day , month , year ,from , to, i = 0;
            do {
                if (i++ > 0) System.out.println("Invalid date!! Please Enter a valid date:");
                System.out.print("Please enter the year : ");
                year = in.nextInt();

                System.out.print("Please enter the month : ");
                month = in.nextInt();

                System.out.print("Please enter the day : ");
                day = in.nextInt();

                date = new Date(day, month, year);
            } while(!date.valid());
            i = 0; boolean foundFrom, foundTo;
            do {
                if (i++ > 0) System.out.println("Invalid times!");
                List<Integer> availableHours = s.get(c).showAvailableHours(date);
                foundFrom = false; foundTo = false;
                System.out.println("***********Avaliable Hours***********");
                System.out.println(availableHours);
                System.out.print("Please enter the time from : ");
                from = in.nextInt();
                for (Integer hour : availableHours) if (hour == from) {foundFrom = true; break;}
                System.out.print("Please enter the time to : ");
                to = in.nextInt();
                for (Integer hour : availableHours) if (hour == to) {foundTo = true; break;}
            } while(from > to || !foundFrom || !foundTo);
            s.get(c).makeBooking(this, date, from, to);
            System.out.println("Booking was succesfull");
        }
        //in.close();
    }
    @Override
    public String toString() {
        return "Player [id=" + id + ", name=" + name + ", dob=" + dob + ", address=" + address + ", mobile=" + mobile
                + ", email=" + email + ", username=" + username + ", password=" + password + "]";
    }
}
