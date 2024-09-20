//Heba Mustafa 1221916
//Lab 4
//Lecture Section 3
package proj_1221916_s4;

public abstract class CustomerPayment implements Comparable<CustomerPayment>{
protected String customerName;
protected int customerId;
protected double amount;
public static int authorizedCount=0;


public CustomerPayment() {
	this.customerName = "";
    this.customerId = 0;
    this.amount = 0;
}
public CustomerPayment(String customerName, int customerId, double amount) {
	this.customerName = customerName;
	this.customerId = customerId;
	this.amount = amount;
}


public String getCustomerName() {
	return customerName;
}
public void setCustomerName(String customerName) {
	this.customerName = customerName;
}
public int getCustomerId() {
	return customerId;
}
public void setCustomerId(int customerId) {
	this.customerId = customerId;
}
public double getAmount() {
	return amount;
}
public void setAmount(double amount) {
	this.amount = amount;
}


@Override
public String toString() {
	return "CustomerPayment [customerName=" + customerName + ", customerId=" + customerId + ", amount=" + amount + "]";
}
//methods 

protected abstract double calculatePayment();
//prints the properties and the calculated payment by calling both the toString() as well as the calculatePayment() methods
void printPaymentInfo() {
	  System.out.println(toString());
      System.out.println("Payment: " + calculatePayment());
  }
public int compareTo(CustomerPayment payment) {
if(this.calculatePayment()>payment.calculatePayment())
	return -1; 
else if(this.calculatePayment()<payment.calculatePayment())
return 1; 
else
	return 0;
}
}

