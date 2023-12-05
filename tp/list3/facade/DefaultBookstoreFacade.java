package eu.jpereira.trainings.designpatterns.structural.facade;

import eu.jpereira.trainings.designpatterns.structural.facade.model.Book;
import eu.jpereira.trainings.designpatterns.structural.facade.model.Customer;
import eu.jpereira.trainings.designpatterns.structural.facade.model.DispatchReceipt;
import eu.jpereira.trainings.designpatterns.structural.facade.model.Order;
import eu.jpereira.trainings.designpatterns.structural.facade.service.BookDBService;
import eu.jpereira.trainings.designpatterns.structural.facade.service.CustomerDBService;
import eu.jpereira.trainings.designpatterns.structural.facade.service.CustomerNotificationService;
import eu.jpereira.trainings.designpatterns.structural.facade.service.OrderingService;
import eu.jpereira.trainings.designpatterns.structural.facade.service.WharehouseService;

public class DefaultBookstoreFacade implements BookstoreFacade {
    private BookDBService bookService;
    private CustomerDBService customerService;
    private CustomerNotificationService customerNotificationService;
    private OrderingService orderingService;
    private WharehouseService warehouseService;

    @Override
    public void placeOrder(String customerId, String isbn) {
        final Book book = this.bookService.findBookByISBN(isbn);
		final Customer customer = this.customerService.findCustomerById(customerId);
        final Order order = this.orderingService.createOrder(customer, book);
		final DispatchReceipt dispatchReceipt = this.warehouseService.dispatch(order);
        this.customerNotificationService.notifyClient(dispatchReceipt);
    }

    public void setBookService(BookDBService bookService) {
        this.bookService = bookService;
    }

    public void setCustomerService(CustomerDBService customerService) {
        this.customerService = customerService;
    }

    public void setCustomerNotificationService(CustomerNotificationService customerNotificationService) {
        this.customerNotificationService = customerNotificationService;
    }

    public void setOrderingService(OrderingService orderingService) {
        this.orderingService = orderingService;
    }

    public void setWarehouseService(WharehouseService warehouseService) {
        this.warehouseService = warehouseService;
    }
}
