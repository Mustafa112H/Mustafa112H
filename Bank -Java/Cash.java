//Heba Mustafa 1221916
//Lab 4
//Lecture Section 3
package proj_1221916_s4;

public class Cash extends CustomerPayment {
private double discountRate;

	public Cash() {
		   super();
	       this.discountRate = 0;
}


	public Cash(String customerName, int customerId, double amount,double discountRate) {
		super(customerName, customerId, amount);
		this.discountRate=discountRate;
	}


	

	public double getDiscountRate() {
		return discountRate;
	}

	public void setDiscountRate(double discountRate) {
		this.discountRate = discountRate;
	}

	@Override
	public String toString() {
		return "Cash [discountRate=" + discountRate + ", customerName=" + customerName + ", customerId=" + customerId
				+ ", amount=" + amount + "]";
	}

	@Override
	protected double calculatePayment() {
		
		return amount-(amount*(discountRate/100));
	}
}
