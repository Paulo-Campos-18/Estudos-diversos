using Exercico_final.Entities;
using Exercico_final.Entities.Enums;
using System.Globalization;

Console.WriteLine("Enter cliente data:");
Console.Write("Name: ");
string name = Console.ReadLine();
Console.Write("Email: ");
string email = Console.ReadLine();
Console.Write("Birth date (DD/MM/YYYY): ");
string birthDate= Console.ReadLine();
Console.Write("Status: (PENDING_PAYMENT/ PROCESSING/ SHIPPED/ DELIVERED) ");
OrderStatus status = Enum.Parse<OrderStatus>(Console.ReadLine().ToUpper());
Console.Write("How many items to this order? ");
int n = int.Parse(Console.ReadLine());

Client client = new Client(name,email,DateTime.Parse(birthDate));
Order order = new Order(status);
order.addClient(client);

for(int i = 0; i < n; i++)
{
    Console.WriteLine($"\nEnter #{i + 1} item data:");
    Console.Write("Product name: ");
    string pName = Console.ReadLine();
    Console.Write("Product price: ");
    double pPrice = double.Parse(Console.ReadLine(),CultureInfo.InvariantCulture);
    Console.Write("Quantity: ");
    int pQuantity = int.Parse(Console.ReadLine());

    Product p = new Product(pName,pPrice);
    OrderItem orderItem = new OrderItem(pQuantity, pPrice);
    orderItem.addProduct(p);
    order.addItem(orderItem);
}
Console.WriteLine(order);



