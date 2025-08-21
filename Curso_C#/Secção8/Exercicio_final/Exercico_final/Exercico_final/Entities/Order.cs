using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Exercico_final.Entities.Enums;
using System.Globalization;

namespace Exercico_final.Entities
{
    internal class Order
    {
        public DateTime Moment { get; set; } = DateTime.Now;
        public OrderStatus Status { get; set; }
        public List<OrderItem> Itens { get; set; } = new List<OrderItem>();
        public Client Client { get; set; }

        public void addClient(Client client)
        {
            if (Client == null)
            {
                Client = client;
            }
            else { Console.WriteLine("Error: Essa Order já possui um cliente"); }
        }

        public void addItem(OrderItem item)
        {
            Itens.Add(item);
        }
        public void removeItem(OrderItem item)
        { 
            Itens.Remove(item); 
        }

        public double total()
        {
            double sum = 0;
            foreach(OrderItem item in Itens)
            {
                sum += item.subTotal();
            }
            return sum;
        }

        public Order(OrderStatus status)
        {
            Status = status;
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("\nORDER SUMMARY");
            sb.Append("Order moment: ");
            sb.AppendLine(Moment.ToString("dd/MM/yyyy HH:mm:ss"));
            sb.Append("Order statis: ");
            sb.AppendLine(Status.ToString());
            sb.Append("Client: ");
            sb.Append(Client.Name);
            sb.Append(Client.BirthDate.ToString(" (dd/MM/yyyy) - "));
            sb.AppendLine(Client.Email);
            sb.AppendLine("Order Items:");
            
            foreach(OrderItem item in Itens)
            {
                sb.Append(item.Product.Name + ", ");
                sb.Append($"${item.Price.ToString("F2",CultureInfo.InvariantCulture)}, ");
                sb.Append($"Quantity: {item.Quantity}, ");
                sb.AppendLine($"Subtotal: ${item.subTotal().ToString("F2", CultureInfo.InvariantCulture)}");

            }
                sb.AppendLine($"Total price: ${total().ToString("F2", CultureInfo.InvariantCulture)}");
            
            return sb.ToString();
        }
    }
}
