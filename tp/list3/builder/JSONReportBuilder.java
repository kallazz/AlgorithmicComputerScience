package eu.jpereira.trainings.designpatterns.creational.builder;

import java.util.Iterator;
import java.util.List;

import eu.jpereira.trainings.designpatterns.creational.builder.json.JSONReportBody;
import eu.jpereira.trainings.designpatterns.creational.builder.model.Report;
import eu.jpereira.trainings.designpatterns.creational.builder.model.SoldItem;

public class JSONReportBuilder implements ReportBuilder {
    private JSONReportBody reportBody;
    private final String customerName;
    private final String customerPhone;
    private final List<SoldItem> items;

    public JSONReportBuilder(final String customerName, final String customerPhone, final List<SoldItem> items) {
        this.reportBody = new JSONReportBody();
        this.customerName = customerName;
        this.customerPhone = customerPhone;
        this.items = items;
    }

    @Override
    public void buildCustomerInfo() {
        reportBody.addContent("sale:{customer:{");
        reportBody.addContent("name:\"");
        reportBody.addContent(customerName);
        reportBody.addContent("\",phone:\"");
        reportBody.addContent(customerPhone);
        reportBody.addContent("\"}");
    }

    @Override
    public void buildItems() {
        reportBody.addContent(",items:[");
        Iterator<SoldItem> it = items.iterator();
        while ( it.hasNext() ) {
            SoldItem item = it.next();
            reportBody.addContent("{name:\"");
            reportBody.addContent(item.getName());
            reportBody.addContent("\",quantity:");
            reportBody.addContent(String.valueOf(item.getQuantity()));
            reportBody.addContent(",price:");
            reportBody.addContent(String.valueOf(item.getUnitPrice()));
            reportBody.addContent("}");
            if ( it.hasNext() ) {
                reportBody.addContent(",");
            }
        }
        reportBody.addContent("]}");
    }

    @Override
    public Report getReport() {
        Report report = new Report();
        report.setReportBody(reportBody);
        return report;
    }
}
