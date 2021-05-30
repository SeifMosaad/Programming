package model;

import java.io.Serializable;
import java.util.*;

import model.Date;
import model.Booking;

public class Playground implements Serializable {
    public static int bookingId = 0;
    public static long playgroundId = 0;

    private long id;
    private String name;
    private String location;
    private Double size;
    private int pricePerHour;
    private int cancellationPeriod;
    private HashMap<String, ArrayList<Integer>> availableHours;
    private int status;
    private List<Booking> bookings;

    // constructors
    public Playground(){
        this.id = playgroundId++;
        availableHours = new HashMap<String, ArrayList<Integer>>();
        bookings = new ArrayList<Booking>();
        this.status = 1;
    }
    public Playground(String name, String location, Double size, int pricePerHour, int cancellationPeriod, int status){
        this.name = name; this.location = location; this.size = size; this.pricePerHour = pricePerHour;
        this.cancellationPeriod = cancellationPeriod; this.status = status;

        this.id = playgroundId++;
        availableHours = new HashMap<String, ArrayList<Integer>>();
        bookings = new ArrayList<Booking>();
    }

    // setters & getters
    public long getId() {
        return id;
    }
    public void setId(long id) {
        this.id = id;
    }
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public String getLocation() {
        return location;
    }
    public void setLocation(String location) {
        this.location = location;
    }
    public Double getSize() {
        return size;
    }
    public void setSize(Double size) {
        this.size = size;
    }
    public int getPricePerHour() {
        return pricePerHour;
    }
    public void setPricePerHour(int pricePerHour) {
        this.pricePerHour = pricePerHour;
    }
    public int getCancellationPeriod() {
        return cancellationPeriod;
    }
    public void setCancellationPeriod(int cancellationPeriod) {
        this.cancellationPeriod = cancellationPeriod;
    }
    public HashMap<String, ArrayList<Integer>> getAvailableHours() {
        return new HashMap<String, ArrayList<Integer>>(availableHours);
    }
    public void setAvailableHours(HashMap<String, ArrayList<Integer>> availableHours) {
        this.availableHours = availableHours;
    }
    public int getStatus() {
        return status;
    }
    public void setStatus(int status) {
        this.status = status;
    }
    public List<Booking> getBookings() {
        return new ArrayList<Booking>(bookings);
    }
    public void setBookings(List<Booking> bookings) {
        this.bookings = bookings;
    }


    // EFFECTS: returns a list of available hours for the given date
    public List<Integer> showAvailableHours(Date date){
        List<Integer> ret = new ArrayList<Integer>();
        if (availableHours.containsKey(date.getDate())) ret = availableHours.get(date.getDate());
        else for (int i = 0; i < 24; ++i) ret.add(i);
        int cur_hr = Calendar.getInstance().get(Calendar.HOUR_OF_DAY);
        if (date.today())
            for (int i = 0; i < ret.size(); ++i) if (ret.get(i) <= cur_hr) ret.remove(i--);
        return new ArrayList<Integer>(ret);
    }

    // REQUIRES: Given date and time are available
    // MODIFIES: this
    // EFFECTS: adds a new booking in bookings, returns true if operation was successful
    public boolean makeBooking(Player p, Date date, int from, int to){
        Booking booking = new Booking(bookingId++, p, date, from, to, status);
        bookings.add(booking);
        if (!availableHours.containsKey(date.getDate())) {
            availableHours.put(date.getDate(), new ArrayList<Integer>(
                    Arrays.asList(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 ,16, 17, 18, 19, 20, 21, 22, 23)));
        }
        List<Integer> list = availableHours.get(date.getDate());
        for (int i = 0; i < list.size(); ++i) if (list.get(i) >= from && list.get(i) <= to) list.remove(i--);

        return true;
    }

    // REQUIRES: Given id has to exist in bookings
    // MODIFIES: this
    // EFFECTS: removes a booking from bookings returns true if operation is successful
    public boolean cancelBooking(int bid){
        int i;
        for (i = 0; i < bookings.size(); ++i)
            if (bookings.get(i).getId() == bid) {  break; }

        List<Integer> list = availableHours.get(bookings.get(i).getDate().getDate());
        for(int t = bookings.get(i).getFrom(); t <= bookings.get(i).getTo(); ++t) list.add(t);
        Collections.sort(list);
        bookings.remove(i);

        return true;
    }
}
