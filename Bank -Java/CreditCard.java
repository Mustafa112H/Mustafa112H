//Heba Mustafa 1221916
//Lab 4
//Lecture Section 3
package proj_1221916_s4;
import java.util.*;
public class CreditCard extends CustomerPayment implements Payable {
private double chargingFee;
private Date expiryDate;

	public CreditCard() {
		 super();
	     this.chargingFee=0;
	     this.expiryDate = new Date();
	}

	public CreditCard(String customerName, int customerId, double amount, double chargingFee, Date expiryDate) {
		super(customerName, customerId, amount);
		this.chargingFee=chargingFee;
		this.expiryDate= expiryDate;
	}

	public double getChargingFee() {
		return chargingFee;
	}

	public void setChargingFee(double chargingFee) {
		this.chargingFee = chargingFee;
	}

	public Date getExpiryDate() {
		return expiryDate;
	}

	public void setExpiryDate(Date expiryDate) {
		this.expiryDate = expiryDate;
	}


	@Override
	public String toString() {
		return "CreditCard [chargingFee=" + chargingFee + ", expiryDate=" + expiryDate + ", customerName="
				+ customerName + ", customerId=" + customerId + ", amount=" + amount + "]";
	}
//A CreditCard payment is authorized if its expiryDate is greater than or equal to the current date
	@Override
	public boolean isAuthorized() {
		
        if(expiryDate.compareTo(new Date())>=0) {
            return true;
        }

        return false;
    }

	@Override
	protected double calculatePayment() {
		
		return amount+chargingFee;
	}
	

}
