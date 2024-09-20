//Heba Mustafa 1221916
//Lab 4
//Lecture Section 3
package proj_1221916_s4;

public class Check extends CustomerPayment implements Payable{
	static final int CASHIER=1, CERTIFIED=2, PERSONAL=3; 
private int accountNumber;
private double accountBalance;
private int type; 



	public Check() {
		super();
	    this.accountNumber = 0;
	    this.accountBalance = 0;
	    this.type = 0;
}	
	public Check(String customerName, int customerId, double amount, int accountNumber, double accountBalance, int type) {
		super(customerName, customerId, amount);
		this.accountNumber = accountNumber;
		this.accountBalance = accountBalance;
		this.type = type;
		
	}

	public int getAccountNumber() {
		return accountNumber;
	}

	public void setAccountNumber(int accountNumber) {
		this.accountNumber = accountNumber;
	}

	public double getAccountBalance() {
		return accountBalance;
	}

	public void setAccountBalance(double accountBalance) {
		this.accountBalance = accountBalance;
	}

	public int getType() {
		return type;
	}

	public void setType(int type) {
		this.type = type;
	}


	@Override
	public String toString() {
		return "Check [accountNumber=" + accountNumber + ", accountBalance=" + accountBalance + ", type=" + type
				+ ", customerName=" + customerName + ", customerId=" + customerId + ", amount=" + amount + "]";
	}
//A Check payment is authorized if either the type of the check is CASHIER 
//or if the amount of the payment is less than or equal to the accountBalance, otherwise it is not authorized. 
	@Override
	public boolean isAuthorized() {
		if(type==CASHIER||amount<=accountBalance) {
			 if(type != CASHIER)
	        deductAmountFromBalance();
			return true;}
		else
		return false;
	}

	@Override
	protected double calculatePayment() {
        return amount;
	}
	public void deductAmountFromBalance() {
		 accountBalance -= getAmount();
	}

}
