package eu.jpereira.trainings.designpatterns.creational.builder;

import java.util.Iterator;
import java.util.List;

import eu.jpereira.trainings.designpatterns.creational.builder.model.Report;
import eu.jpereira.trainings.designpatterns.creational.builder.model.SoldItem;

public class HTMLReportBuilder implements ReportBuilder {
    private HTMLReportBody reportBody;
    private final String customerName;
    private final String customerPhone;
    private final List<SoldItem> items;

    public HTMLReportBuilder(final String customerName, final String customerPhone, final List<SoldItem> items) {
        this.reportBody = new HTMLReportBody();
        this.customerName = customerName;
        this.customerPhone = customerPhone;
        this.items = items;
    }

    @Override
    public void buildCustomerInfo() {
        reportBody.putContent("<span class=\"customerName\">");
        reportBody.putContent(customerName);
        reportBody.putContent("</span><span class=\"customerPhone\">");
        reportBody.putContent(customerPhone);
        reportBody.putContent("</span>");
    }

    @Override
    public void buildItems() {
        reportBody.putContent("<items>");

        Iterator<SoldItem> it = items.iterator();
        while ( it.hasNext() ) {
            SoldItem soldEntry= it.next();
            reportBody.putContent("<item><name>");
            reportBody.putContent(soldEntry.getName());
            reportBody.putContent("</name><quantity>");
            reportBody.putContent(soldEntry.getQuantity());
            reportBody.putContent("</quantity><price>");
            reportBody.putContent(soldEntry.getUnitPrice());
            reportBody.putContent("</price></item>");
        }
        reportBody.putContent("</items>");
    }

    @Override
    public Report getReport() {
        Report report = new Report();
        report.setReportBody(reportBody);
        return report;
    }
}
