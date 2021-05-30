package test;


import model.Date;
import model.Player;
import model.Playground;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import org.junit.Before;
import org.junit.Test;

import static junit.framework.TestCase.assertEquals;

public class PlaygroundTest {
    String testName;
    String testLocation;
    Double testSize;
    int testPricePerHour;
    int testCancellationPeriod;
    int testStatus;
    Player testPlayer;
    Date testDate;
    Playground testPlayground;
    @Before
    public void setUp(){
        testName = "test name";
        testLocation = "test street, testier governorate, testiest city ";
        testSize = 100.15;
        testPricePerHour = 10;
        testCancellationPeriod = 10;
        testStatus = 4;
        testPlayer = new Player();
        testDate = new Date(10, 11, 2300);
        testPlayground = new Playground(testName, testLocation, testSize, testPricePerHour, testCancellationPeriod, testStatus);
    }

    @Test
    public void testConstructors(){
        assertEquals(Playground.playgroundId - 1, testPlayground.getId());
        assertEquals(testName, testPlayground.getName());
        assertEquals(testLocation, testPlayground.getLocation());
        assertEquals(testSize, testPlayground.getSize());
        assertEquals(testPricePerHour, testPlayground.getPricePerHour());
        assertEquals(testCancellationPeriod, testPlayground.getCancellationPeriod());
        assertEquals(testStatus, testPlayground.getStatus());
        assertEquals(true, testPlayground.getAvailableHours().isEmpty());
        assertEquals(true, testPlayground.getBookings().isEmpty());

        Playground p2 = new Playground();
        assertEquals(Playground.playgroundId - 1, p2.getId());
    }

    @Test
    public void testShowAvailableHours(){
        List<Integer> testAvailableHours = new ArrayList<Integer>(
                Arrays.asList(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23));

        assertEquals(true, testAvailableHours.equals(testPlayground.showAvailableHours(testDate)));
    }

    @Test
    public void testMakeBookingEmptyDate(){
        testPlayground.makeBooking(testPlayer, testDate, 12, 14);
        int testValue = -1;
        if (!testPlayground.getBookings().isEmpty()) testValue = testPlayground.getBookings().get(0).getId();
        assertEquals(Playground.bookingId - 1, testValue);
        List<Integer> testAvailableHours = new ArrayList<Integer>(
                Arrays.asList(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 15, 16, 17, 18, 19, 20, 21, 22, 23));

        assertEquals(true, testAvailableHours.equals(testPlayground.showAvailableHours(testDate)));
    }

    @Test
    public void testMakeBooking(){
        testPlayground.makeBooking(testPlayer, testDate, 12, 14);
        testPlayground.makeBooking(testPlayer, testDate, 9, 10);
        int testValue = -1;
        if (!testPlayground.getBookings().isEmpty()) testValue = testPlayground.getBookings().get(0).getId();
        assertEquals(Playground.bookingId - 2, testValue);

        testValue = -1;
        if (!testPlayground.getBookings().isEmpty()) testValue = testPlayground.getBookings().get(1).getId();
        assertEquals(Playground.bookingId - 1, testValue);

        List<Integer> testAvailableHours = new ArrayList<Integer>(
                Arrays.asList(0, 1, 2, 3, 4, 5, 6, 7, 8, 11, 15, 16, 17, 18, 19, 20, 21, 22, 23));

        assertEquals(true, testAvailableHours.equals(testPlayground.showAvailableHours(testDate)));

        testPlayground.makeBooking(testPlayer, testDate, 22, 23);
        testValue = -1;
        if (!testPlayground.getBookings().isEmpty()) testValue = testPlayground.getBookings().get(2).getId();
        assertEquals(Playground.bookingId - 1, testValue);

        testAvailableHours = new ArrayList<Integer>(
                Arrays.asList(0, 1, 2, 3, 4, 5, 6, 7, 8, 11, 15, 16, 17, 18, 19, 20, 21));

        assertEquals(true, testAvailableHours.equals(testPlayground.showAvailableHours(testDate)));
    }

    @Test
    public void testCancelBooking(){
        testPlayground.makeBooking(testPlayer, testDate, 12, 14);
        testPlayground.makeBooking(testPlayer, testDate, 9, 10);
        assertEquals(testPlayground.getBookings().size(), 2);
        testPlayground.cancelBooking(0);
        assertEquals(testPlayground.getBookings().size(), 1);
        int testValue = -1;
        if (!testPlayground.getBookings().isEmpty()) testValue = testPlayground.getBookings().get(0).getId();
        assertEquals(Playground.bookingId - 1, testValue);

        List<Integer> testAvailableHours = new ArrayList<Integer>(
                Arrays.asList(0, 1, 2, 3, 4, 5, 6, 7, 8, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23));
        assertEquals(true, testAvailableHours.equals(testPlayground.showAvailableHours(testDate)));
    }
}

