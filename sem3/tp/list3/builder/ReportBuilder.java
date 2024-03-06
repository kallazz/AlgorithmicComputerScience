package eu.jpereira.trainings.designpatterns.creational.builder;

import eu.jpereira.trainings.designpatterns.creational.builder.model.Report;

public interface ReportBuilder {
    public void buildCustomerInfo();
    public void buildItems();
    public Report getReport();
}
