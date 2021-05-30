package model;

import java.io.Serializable;

public class Booking implements Serializable{
    int id;
    Player bookingPlayer;
    Date date;
    int from;
    int to;
    int status;

    public Booking(int id, Player bookingPlayer, Date date, int from, int to, int status) {
        this.id = id;
        this.bookingPlayer = bookingPlayer;
        this.date = date;
        this.from = from;
        this.to = to;
        this.status = status;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Player getBookingPlayer() {
        return bookingPlayer;
    }

    public void setBookingPlayer(Player bookingPlayer) {
        this.bookingPlayer = bookingPlayer;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public int getFrom() {
        return from;
    }

    public void setFrom(int from) {
        this.from = from;
    }

    public int getTo() {
        return to;
    }

    public void setTo(int to) {
        this.to = to;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    boolean cancel(){
        return true;
    }
    boolean pay(){
        return true;
    }
}
