package eu.jpereira.trainings.designpatterns.creational.builder;

import eu.jpereira.trainings.designpatterns.creational.builder.model.Report;

public class ReportBuildDirector {
    private final ReportBuilder builder;


    public ReportBuildDirector(ReportBuilder builder) {
        this.builder = builder;
    }

    public void build() {
        builder.buildCustomerInfo();
        builder.buildItems();
    }

    public Report getReport() {
        return this.builder.getReport();
    }
}
