/* Create an array named products which you will use to add all of your product object literals that you create in the next step. */
const products = [];
/* Create 3 or more product objects using object literal notation 
   Each product should include five properties
   - name: name of product (string)
   - price: price of product (number)
   - quantity: quantity in cart should start at zero (number)
   - productId: unique id for the product (number)
   - image: picture of product (url string)
*/
const product1 = {
  name: "cherry",
  price: 15.2,
  quantity: 0,
  productId: 1,
  image: "./images/cherry.jpg"

}
const product2 = {
  name: "orange",
  price: 12.1,
  quantity: 0,
  productId: 2,
  image: "./images/orange.jpg"

}
const product3 = {
  name: "strawberry",
  price: 25,
  quantity: 0,
  productId: 3,
  image: "./images/strawberry.jpg"

}
products.push(product1, product2, product3)
/* Images provided in /images folder. All images from Unsplash.com
   - cherry.jpg by Mae Mu
   - orange.jpg by Mae Mu
   - strawberry.jpg by Allec Gomes
*/

/* Declare an empty array named cart to hold the items in the cart */
const cart = []
/* Create a function named addProductToCart that takes in the product productId as an argument
  - addProductToCart should get the correct product based on the productId
  - addProductToCart should then increase the product's quantity
  - if the product is not already in the cart, add it to the cart
*/
//this function will find the product that we want to do changes on 
//it will find it using the productId
function findProduct(productId){
  let product = "";
  //loops through the products and looks for the one with the 
  //matching id
  for(let i = 0; i < products.length; i++)
    if (products[i].productId === productId)
      product = products[i];
      //returns the wanted product
  return product;
}

//this function adds the products to the cart if its not already
//if its already in the cart it wil increment the quantity
function addProductToCart(productId){
  let product = findProduct(productId);
  if(product.quantity === 0)
  cart.push(product);
  product.quantity++;

}

/* Create a function named increaseQuantity that takes in the productId as an argument
  - increaseQuantity should get the correct product based on the productId
  - increaseQuantity should then increase the product's quantity
*/
//this function will increase the quantity
function increaseQuantity(productId){
  let product = findProduct(productId);
  product.quantity++;
  
  }
/* Create a function named decreaseQuantity that takes in the productId as an argument
  - decreaseQuantity should get the correct product based on the productId
  - decreaseQuantity should decrease the quantity of the product
  - if the function decreases the quantity to 0, the product is removed from the cart
*/
//function that will decrease the quantity and remove the product if the quantity reaches zero
function decreaseQuantity(productId){
  let product = findProduct(productId);
  product.quantity--;
  //if the quantity reaches zero we need to remove it from the cart
  if(product.quantity === 0){
    const index = cart.indexOf(product);
    cart.splice(index, 1);
}
  
  }
/* Create a function named removeProductFromCart that takes in the productId as an argument
  - removeProductFromCart should get the correct product based on the productId
  - removeProductFromCart should update the product quantity to 0
  - removeProductFromCart should remove the product from the cart
*/
//this will remove a product that we dont want anymore from the cart
function removeProductFromCart(productId){
  //finds the product
  let product = findProduct(productId);
  //sets the quantity to zero 
  product.quantity = 0;
  //removes it from cart
  const index = cart.indexOf(product);
  cart.splice(index, 1);
  
  }
/* Create a function named cartTotal that has no parameters
  - cartTotal should iterate through the cart to get the total of all products
  - cartTotal should return the sum of the products in the cart
*/
//this function will calculate the total amount that needs to be payed
function cartTotal(){
  let total = 0;
  //goes through the cart checks each price and checks how many of that product there is
  //multiplies them and adds all the products to get the amount needed
  for(let i = 0 ; i < cart.length; i++){
    total += cart[i].price*cart[i].quantity;

  }
  return total;
}
/* Create a function called emptyCart that empties the products from the cart */
//this will empty the cart
function emptyCart() {
  cart.splice(0, cart.length); // Remove all items from the cart
}
/* Create a function named pay that takes in an amount as an argument
  - pay will return a negative number if there is a remaining balance
  - pay will return a positive number if money should be returned to customer
*/
//variable to track the amount paid
let totalPaid = 0;

function pay(amount) {
  // Add the amount paid to the total amount
  totalPaid += amount;
  // Calculate the remaining amount after purchasing
  let remaining = totalPaid - cartTotal();
  // Check if the payment is enough
  if (remaining >= 0) {
    // Reset totalPaid to zero for next purchase
    totalPaid = 0;
    // Empty the cart
    emptyCart();
  }
  return remaining;
}
/* Place stand out suggestions here (stand out suggestions can be found at the bottom of the project rubric.)*/


/* The following is for running unit tests. 
   To fully complete this project, it is expected that all tests pass.
   Run the following command in terminal to run tests
   npm run test
*/

module.exports = {
  products,
  cart,
  addProductToCart,
  increaseQuantity,
  decreaseQuantity,
  removeProductFromCart,
  cartTotal,
  pay, 
  emptyCart
  /* Uncomment the following line if completing the currency converter bonus */
  // currency
}