import java.io.BufferedReader;
import static java.nio.file.StandardCopyOption.*;
import java.nio.file.Files;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.io.FileWriter;
import java.io.File;
import java.io.BufferedWriter;

class backend {
    final static String NEW_ACCOUNTS_FILENAME = "new_accounts.txt";
    final static String ERROR_LOG_FILENAME = "error_log.txt";
    final static String NEW_TICKETS_FILENAME = "new_tickets.txt";

    final static int TICKETS_LOG_SIZE = 3;
    final static int TICKETS_PRICE_SIZE = 6;
    final static int CREDIT_FLOAT_SIZE = 9;
    final static int BUYERNAME_SIZE = 15;
    final static int SELLER_NAME_SIZE = 15;
    final static int EVENT_NAME_SIZE = 19;
    final static int TICKET_NUM_SIZE = 3;
    final static int USERNAME_SIZE = 15;
    final static int USER_TYPE_SIZE = 2;
    final static int LOG_TYPE_SIZE = 2;

    final static String LOG_CREATE_TRANSACTIONCODE = "01";
    final static String LOG_DELETE_TRANSACTIONCODE = "02";
    final static String LOG_ADD_CREDIT_TRANSACTIONCODE = "06";
    final static String LOG_END_OF_SESSION_TRANSACTIONCODE = "00";
    final static String LOG_REFUND_TRANSACTIONCODE = "05";
    final static String LOG_SELL_TRANSACTIONCODE = "03";
    final static String LOG_BUY_TRANSACTIONCODE = "04";
    //prep these to be used later if arguments are called correctly
    static String mergedDTFilename = null; 
    static String oldAccountsFilename = null;
    static String oldTicketsFilename = null;

    //used to keep track of how much credit is given per session. 
    //gets cleared when Endsession is called. Gets added when addCredit is called.
    //If over 1000.00 the addCredit will fail
    static float creditPerSession = 0.0f;

    public static void main(String[] args) {
        //Checks if 3 arguments are present, if not print usage info
        if(args.length < 3){
            System.out.println("ERROR: no arguments specified\n");
            System.out.println("==backend==");
            System.out.println("Takes in files generated by the front ends, checks for consistencies/errors and outputs a valid accounts.txt and tickets.txt for use the next day. Generates a log of errors encountered"); 
            System.out.println("Usage: backend <merged_DT> <accounts file> <tickets file>\n");
            System.out.println("<merged_DT> is the Merged Daily Transaction File in text format");
            System.out.println("<accounts file> is the old accounts.txt");
            System.out.println("<tickets file> is the old tickets.txt");
            System.exit(0);
        }
        else{
            //sets the values above to valid entries based on user args
            mergedDTFilename = args[0];
            oldAccountsFilename = args[1];
            oldTicketsFilename = args[2];
            //Copy old accounts to new location to be used
            File oldAccountsFile = new File(oldAccountsFilename);
            File newAccountsFile = new File(NEW_ACCOUNTS_FILENAME);
            try{
                Files.copy(oldAccountsFile.toPath(), newAccountsFile.toPath(), REPLACE_EXISTING);
            }catch(Exception e){
                e.printStackTrace(System.out);
            }

            //Copy old Tickets to a new location to be used
            File oldTicketsFile = new File(oldTicketsFilename);
            File newTicketsFile = new File(NEW_TICKETS_FILENAME);
            try{
                Files.copy(oldTicketsFile.toPath(), newTicketsFile.toPath(), REPLACE_EXISTING);
            }catch(Exception e){
                e.printStackTrace(System.out);
            }
        }

        //Read the merged daily transaction file line by line
        //Each function ending with DT is used to handle the various transaction codes
        //See top of file for constants for each transaction type
        //Each function will return a String. Null means it succedded, anything else means
        //there was an error and that error message will be returned to be passed to ErrorWriter
        try (BufferedReader br = new BufferedReader(new FileReader(mergedDTFilename))) {
            String returnedErrorStatus = null;
            String line;
            while ((line = br.readLine()) != null) {
                //switch on the transaction type before doing the changes
                String type = line.substring(0, 2);
                switch (type) {
                    case LOG_CREATE_TRANSACTIONCODE:
                        returnedErrorStatus = CreateDT(line);
                        if(returnedErrorStatus != null){
                            ErrorWriter(returnedErrorStatus);
                        }
                        break;

                    case LOG_DELETE_TRANSACTIONCODE:
                        returnedErrorStatus = DeleteDT(line);
                        if(returnedErrorStatus != null){
                            ErrorWriter(returnedErrorStatus);
                        }
                        break;
                    case LOG_ADD_CREDIT_TRANSACTIONCODE:
                        returnedErrorStatus = AddCreditDT(line);
                        if(returnedErrorStatus != null){
                            ErrorWriter(returnedErrorStatus);
                        }
                        break;
                    case LOG_END_OF_SESSION_TRANSACTIONCODE:
                        returnedErrorStatus = EndOfSessionDT(line);
                        if(returnedErrorStatus != null){
                            ErrorWriter(returnedErrorStatus);
                        }
                        break;
                    case LOG_REFUND_TRANSACTIONCODE:
                        returnedErrorStatus = RefundDT(line);
                        if(returnedErrorStatus != null){
                            ErrorWriter(returnedErrorStatus);
                        }
                        break;
                    case LOG_SELL_TRANSACTIONCODE:
                        returnedErrorStatus = BuySellDT(line);
                        if(returnedErrorStatus != null){
                            ErrorWriter(returnedErrorStatus);
                        }
                        break;
                    case LOG_BUY_TRANSACTIONCODE:
                        System.out.println("LOG_BUY");
                        returnedErrorStatus = BuySellDT(line);
                        if(returnedErrorStatus != null){
                            ErrorWriter(returnedErrorStatus);
                        }
                        break;
                    default:
                        System.out.println("TransactionType not found");

                }
            }
        }catch(Exception e){
            e.printStackTrace(System.out);
        }
    }

    //Helper Function for appending error messages to ERROR_LOG_FILENAME
    //Returns true if succedded in writing, false if failed
    static boolean ErrorWriter(String errorMessage){
        try{
            FileWriter fw = new FileWriter(new File(ERROR_LOG_FILENAME), true);
            BufferedWriter out = new BufferedWriter(fw);
            out.write("ERROR: " + errorMessage + '\n');
            out.flush();
            out.close();
        }catch(Exception e){
            e.printStackTrace(System.out);
            return false;
        }
        return true;

    }

    //Helper Function that handles the case where the Transaction type is for Sell or Buy
    //If its a Sell and the eventname/sellername can't be found, add it to the end before END
    //if its a Buy and the eventname/sellername can't be found, fail
    static String BuySellDT(String DTline){
        //Initialize the isFound flag to false
        boolean isFound = false;

        //Initialize where the lines will be stored before writing
        List<String> outputLines = new ArrayList<String>();

        //Find the eventName and sellerName field from the line provided and trim whitespace with trim()
        String untrimmedEventName = DTline.substring(USER_TYPE_SIZE + 1, USER_TYPE_SIZE + 1 + EVENT_NAME_SIZE);
        String eventNameSearch = untrimmedEventName.trim();
        String untrimmedSellerName = DTline.substring(USER_TYPE_SIZE + EVENT_NAME_SIZE + 2, USER_TYPE_SIZE + EVENT_NAME_SIZE + SELLER_NAME_SIZE + 2);
        String sellerNameSearch = untrimmedSellerName.trim();

        //Find the new number of tickets from line provided
        String newTicketAmount = DTline.substring(USER_TYPE_SIZE + EVENT_NAME_SIZE + SELLER_NAME_SIZE + 3, USER_TYPE_SIZE + EVENT_NAME_SIZE + SELLER_NAME_SIZE + TICKET_NUM_SIZE + 3);

        //Find the new price of tickets from line provided
        String newPrice = DTline.substring(USER_TYPE_SIZE + EVENT_NAME_SIZE + SELLER_NAME_SIZE + TICKET_NUM_SIZE + 4, USER_TYPE_SIZE + EVENT_NAME_SIZE + SELLER_NAME_SIZE + TICKET_NUM_SIZE + TICKETS_PRICE_SIZE + 4);

        try (BufferedReader br = new BufferedReader(new FileReader(NEW_TICKETS_FILENAME))) {
            String line;
            //Iterate through all the lines of the new tickets file to find and modify
            //the correct entry
            while ((line = br.readLine()) != null) {
                //check if the line is NOT the end
                if(line.length() > EVENT_NAME_SIZE){
                    String eventNameSuspect = (line.substring(0, EVENT_NAME_SIZE)).trim();
                    String sellerNameSuspect = (line.substring(EVENT_NAME_SIZE + 1, EVENT_NAME_SIZE + SELLER_NAME_SIZE + 1)).trim();
                    //If event and seller exists, then modify it by manipulating tickets #
                    //Take it and store in ArrayList
                    if(eventNameSearch.equals(eventNameSuspect) && sellerNameSearch.equals(sellerNameSuspect)){
                        isFound = true;
                        line = line.substring(0, EVENT_NAME_SIZE + SELLER_NAME_SIZE + 2) + newTicketAmount + ' ' + newPrice;
                    }
                    //Add the line modified or not to the ArrayList if NOT "END" as above
                    outputLines.add(line + '\n');
                }
            }
        }catch(Exception e){
            e.printStackTrace(System.out);
        }

        //If the eventname/sellername combitionation is not found for buy, fail. If its for sell, add it
        //to end of the file
        if(!isFound){
            if(DTline.startsWith(LOG_BUY_TRANSACTIONCODE)){
                return "Eventname: " + eventNameSearch + ", and Sellername: " + sellerNameSearch + " can't be found. Buy not applied";
            }else{
                String newTicketEntry = untrimmedEventName + ' ' + untrimmedSellerName + ' ' + newTicketAmount + ' ' + newPrice;
                outputLines.add(newTicketEntry + '\n');
            }
        }

        //write the file based on the arraylist
        try{
            FileWriter fw = new FileWriter(new File(NEW_TICKETS_FILENAME));
            BufferedWriter out = new BufferedWriter(fw);
            //Iterate through the arraylist adding each line to the file
            for(String s : outputLines){
                 out.write(s);
            }
            out.write("END");
            out.flush();
            out.close();
        }catch(Exception e){
            e.printStackTrace(System.out);
            return "Couldn't write file";
        }
        return null;

    }

    //Helper Function that handles the case where the Transaction type is for Refund
    //If the refunder or the refundee doesn't exist. Fail. Transfer Credit from refunder to
    //refundee's account
    static String RefundDT(String DTline){
        //Initialize the isFound flag to false
        boolean isFound = false;

        //Initialize where the lines will be stored before writing
        List<String> outputLines = new ArrayList<String>();

        //Find the username and refundee field from the line provided and trim whitespace with trim()
        String untrimmedUsernameFiled = DTline.substring(USER_TYPE_SIZE + 1, USER_TYPE_SIZE + 1 + USERNAME_SIZE);
        String usernameSearch = untrimmedUsernameFiled.trim();
        String untrimmedRefundeeField = DTline.substring(USER_TYPE_SIZE + BUYERNAME_SIZE + 2, USER_TYPE_SIZE + BUYERNAME_SIZE + SELLER_NAME_SIZE + 2);
        String refundeeSearch = untrimmedRefundeeField.trim();

        //get the new credit to be change applied
        String refundAmount = DTline.substring(LOG_TYPE_SIZE + BUYERNAME_SIZE + SELLER_NAME_SIZE + 3, LOG_TYPE_SIZE + BUYERNAME_SIZE + SELLER_NAME_SIZE + CREDIT_FLOAT_SIZE + 3);
        //Divide by 100 to normalize to real float
        float refundAmountFloat = Float.parseFloat(refundAmount)/100;

        try (BufferedReader br = new BufferedReader(new FileReader(NEW_ACCOUNTS_FILENAME))) {
            String line;
            //Iterate through all the lines of the new accounts file to find and modify
            //the entry
            while ((line = br.readLine()) != null) {
                //check if the line is NOT the end
                if(line.length() > USERNAME_SIZE){
                    String usernameSuspect = (line.substring(0, USERNAME_SIZE)).trim();
                    //If username exists, then modify it by replacing it with the refund value 
                    //substracted and store it in the ArrayList
                    if(usernameSearch.equalsIgnoreCase(usernameSuspect)){
                        isFound = true;
                        //Find the old credit amount
                        String oldUserCredit = line.substring(USERNAME_SIZE + 2 + USER_TYPE_SIZE, USERNAME_SIZE + 2 + USER_TYPE_SIZE + CREDIT_FLOAT_SIZE);
                        //Divide by 100 to normalize from the string float to real float
                        float oldUserCreditFloat = Float.parseFloat(oldUserCredit)/100;

                        //Substract the new from the old to see the new final amount
                        float newCreditAmount = oldUserCreditFloat - refundAmountFloat;

                        //if newCredit amount is < 0 then return error
                        if(newCreditAmount < 0){
                            return "Credit taken from " + usernameSearch + " will be < 0 (not allowed)";
                        }
                        //Update the creditPerSession to know how much as been added
                        line = line.substring(0, USERNAME_SIZE + USER_TYPE_SIZE + 2) + String.format("%0" + CREDIT_FLOAT_SIZE + "d", (int)(newCreditAmount * 100));
                    }
                    //Add the line modified or not to the ArrayList if NOT "END" as above
                    outputLines.add(line + '\n');
                }
            }
        }catch(Exception e){
            e.printStackTrace(System.out);
        }
        //If the refunder is not found return an error message
        if(!isFound){
            return "Refunder: " + usernameSearch + " not found. Refund NOT applied";
        }
        //Reset isFound to false to start a new search for refundee
        isFound = false;

        //Iterate through the file represented as an ArrayList and find the refundee
        for(String lineFromArray : outputLines){
            //Find the username at that line and trim whitespace
            String usernameSuspect = (lineFromArray.substring(0, USERNAME_SIZE)).trim();
            //Compare it to the refundeed to find if it exists
            if(lineFromArray.length() > USERNAME_SIZE && refundeeSearch.equals(usernameSuspect)){
                isFound = true;
                //Find the old credit amount
                String oldUserCredit = lineFromArray.substring(USERNAME_SIZE + 2 + USER_TYPE_SIZE, USERNAME_SIZE + 2 + USER_TYPE_SIZE + CREDIT_FLOAT_SIZE);
                //Divide by 100 to normalize from the string float to real float
                float oldUserCreditFloat = Float.parseFloat(oldUserCredit)/100;

                //Substract the new from the old to see the new final amount
                float newCreditAmount = oldUserCreditFloat + refundAmountFloat;
                //Update the creditPerSession to know how much as been added
                lineFromArray = lineFromArray.substring(0, USERNAME_SIZE + USER_TYPE_SIZE + 2) + String.format("%0" + CREDIT_FLOAT_SIZE + "d", (int)(newCreditAmount * 100));
            }
        }

        //If the refundee wasn't found, but refunder was, send back error message
        if(!isFound){
            return "Refunder: " + usernameSearch + " found. Refundee: " + refundeeSearch + " not found. Refund NOT applied";
        }

        //Passed all the checks and we're now ready to write the file
        try{
            FileWriter fw = new FileWriter(new File(NEW_ACCOUNTS_FILENAME));
            BufferedWriter out = new BufferedWriter(fw);
            //Iterate through the arraylist adding each line to the file
            for(String s : outputLines){
                 out.write(s);
            }
            out.write("END");
            out.flush();
            out.close();
        }catch(Exception e){
            e.printStackTrace(System.out);
            return "Couldn't write file";
        }

        return null;
    }

    //Helper Function that handles the case where the Transaction type is for EndOfSession
    //Doesn't do much except reset the credit per session
    static String EndOfSessionDT(String DTline){
        creditPerSession = 0.0f;
        return null;
    }

    //Helper Function that handles the case where the Transaction type is for AddCredit
    //If over 1000.00 it will fail. If user doesn't exist, fail
    static String AddCreditDT(String DTline){
        List<String> outputLines = new ArrayList<String>();
        String untrimmedUsernameFiled = DTline.substring(USER_TYPE_SIZE + 1, USER_TYPE_SIZE + 1 + USERNAME_SIZE);
        String usernameSearch = untrimmedUsernameFiled.trim();
        boolean isFound = false;
        try (BufferedReader br = new BufferedReader(new FileReader(NEW_ACCOUNTS_FILENAME))) {
            String line;
            //Iterate through all the lines of the new accounts file to find and modify
            //the entry
            while ((line = br.readLine()) != null) {
                //check if the line is NOT the end
                if(line.length() > USERNAME_SIZE){
                    String usernameSuspect = (line.substring(0, USERNAME_SIZE)).trim();
                    //If username exists, then modify it by replacing it with available credit
                    //And store it in the creditPerSession variable
                    if(usernameSearch.equalsIgnoreCase(usernameSuspect)){
                        isFound = true;
                        //Find the old credit amount
                        String oldUserCredit = line.substring(USERNAME_SIZE + 2 + USER_TYPE_SIZE, USERNAME_SIZE + 2 + USER_TYPE_SIZE + CREDIT_FLOAT_SIZE);
                        //Divide by 100 to normalize from the string float to real float
                        float oldUserCreditFloat = Float.parseFloat(oldUserCredit)/100;

                        //get the new credit to be change to
                        String newUserCredit = DTline.substring(LOG_TYPE_SIZE + USERNAME_SIZE + USER_TYPE_SIZE + 3, LOG_TYPE_SIZE + USERNAME_SIZE + USER_TYPE_SIZE + CREDIT_FLOAT_SIZE + 3);
                        //Divide by 100 to normalize to real float
                        float newUserCreditFloat = Float.parseFloat(newUserCredit)/100;

                        //Substract the new from the old to see how much was added
                        //If its over 1000.00 before end of session call, then Fail
                        float creditDeltaThisTransaction =  newUserCreditFloat - oldUserCreditFloat;
                        float creditDeltaOverall = creditDeltaThisTransaction + creditPerSession;
                        //If the overall credit added for this session is over 1000.00f then fail
                        //Otherwise, make the change to this user's entry before adding to Arraylist
                        if(creditDeltaOverall > 1000.00f){
                            return "Cannot give a credit to " + usernameSearch + " of over 1000.00$ for this session. Credit Not added";
                        }else{
                            //Update the creditPerSession to know how much as been added
                            creditPerSession = creditDeltaOverall;
                            line = line.substring(0, USERNAME_SIZE + USER_TYPE_SIZE + 2) + newUserCredit;
                        }

                    }
                    //Add the line modified or not to the ArrayList if NOT "END" as above
                    outputLines.add(line + '\n');
                }
            }
        }catch(Exception e){
            e.printStackTrace(System.out);
        }

        //If username wasn't found, then return with error
        if(!isFound){
            return "Username: " + usernameSearch + " doesn't exist. No credit Added";
        }

        try{
            FileWriter fw = new FileWriter(new File(NEW_ACCOUNTS_FILENAME));
            BufferedWriter out = new BufferedWriter(fw);
            //Iterate through the arraylist adding each line to the file
            for(String s : outputLines){
                 out.write(s);
            }
            out.write("END");
            out.flush();
            out.close();
        }catch(Exception e){
            e.printStackTrace(System.out);
        }
        return null;
    }

    //Helper Function that handles the case where the Transaction type is for DELETE
    //Checks if the user is already in the new_accounts.txt, if not, return constraints error
    //Otherwise, delete the account and write the file
    static String DeleteDT(String DTline){
        List<String> outputLines = new ArrayList<String>();
        String untrimmedUsernameFiled = DTline.substring(USER_TYPE_SIZE + 1, USER_TYPE_SIZE + 1 + USERNAME_SIZE);
        String usernameSearch = untrimmedUsernameFiled.trim();
        boolean isFound = false;
        try (BufferedReader br = new BufferedReader(new FileReader(NEW_ACCOUNTS_FILENAME))) {
            String line;
            //Iterate through all the lines of the new accounts file to check for if
            //the username is already there
            while ((line = br.readLine()) != null) {
                //check if the line is NOT the end
                if(line.length() > USERNAME_SIZE){
                    String usernameSuspect = (line.substring(0, USERNAME_SIZE)).trim();
                    //If username exists, then set the isFound Flag and DON"T add it to the 
                    //outputLines Array list that will be used to write the new file. Otherwise
                    //add it
                    if(usernameSearch.equalsIgnoreCase(usernameSuspect)){
                        isFound = true;
                    }else{
                        outputLines.add(line + '\n');
                    }
                }
            }
        }catch(Exception e){
            e.printStackTrace(System.out);
        }

        //If username wasn't found, then return with error
        if(!isFound){
            return "Username: " + usernameSearch + " doesn't exist. Didn't delete";
        }

        //Since the name was found in the accounts file, we should write the new file
        //without the entry
        try{
            FileWriter fw = new FileWriter(new File(NEW_ACCOUNTS_FILENAME));
            BufferedWriter out = new BufferedWriter(fw);
            //Iterate through the arraylist adding each line to the file
            for(String s : outputLines){
                 out.write(s);
            }
            out.write("END");
            out.flush();
            out.close();
        }catch(Exception e){
            e.printStackTrace(System.out);
        }
        //Return saying everything succeded
        return null;
    }

    //Helper Function that handles the case where the Transaction type is for Create
    //Checks if the user is already in the new_accounts.txt, if so, return constraints error
    //If not in new_accounts.txt then append to end of the file before "END"
    static String CreateDT(String DTline){
        List<String> outputLines = new ArrayList<String>();
        String untrimmedUsernameFiled = DTline.substring(USER_TYPE_SIZE + 1, USER_TYPE_SIZE + 1 + USERNAME_SIZE);
        String usernameSearch = untrimmedUsernameFiled.trim();
        try (BufferedReader br = new BufferedReader(new FileReader(NEW_ACCOUNTS_FILENAME))) {
            String line;
            //Iterate through all the lines of the old accounts file to check for if
            //the username is already there
            while ((line = br.readLine()) != null) {
                //check if the line is NOT the end
                if(line.length() > USERNAME_SIZE){
                    //Adds the line plus a carriage return to the outputLines arraylist
                    outputLines.add(line + '\n');
                    String usernameSuspect = (line.substring(0, USERNAME_SIZE)).trim();
                    //If the username already exists in the database, return false meaning error
                    if(usernameSearch.equalsIgnoreCase(usernameSuspect)){
                        return "Username: " + usernameSearch + " already exists. Didn't get added";
                    }
                }
            }
        }catch(Exception e){
            e.printStackTrace(System.out);
        }
        //Cut up the original line to get the required info to add to new accounts.txt
        String usernameType = DTline.substring(LOG_TYPE_SIZE + USERNAME_SIZE + 2, LOG_TYPE_SIZE + USERNAME_SIZE + 2 + USER_TYPE_SIZE);
        String userCredit = DTline.substring(LOG_TYPE_SIZE + USERNAME_SIZE + USER_TYPE_SIZE + 3, LOG_TYPE_SIZE + USERNAME_SIZE + USER_TYPE_SIZE + CREDIT_FLOAT_SIZE + 3);

        String newUserInfoLine = untrimmedUsernameFiled + ' ' + usernameType + ' ' + userCredit + '\n';

        //Add the formatted account entry to the outputLines Arraylist
        outputLines.add(newUserInfoLine);
        
        //Since the name wasn't found in accounts, its okay to add it to the new Accounts.txt file
        try{
            FileWriter fw = new FileWriter(new File(NEW_ACCOUNTS_FILENAME));
            BufferedWriter out = new BufferedWriter(fw);
            //Iterate through the arraylist adding each line to the file
            for(String s : outputLines){
                 out.write(s);
            }
            out.write("END");
            out.flush();
            out.close();
        }catch(Exception e){
            e.printStackTrace(System.out);
        }
        //Return saying everything succeded
        return null;
    }
}
