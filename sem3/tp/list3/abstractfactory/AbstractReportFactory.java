package eu.jpereira.trainings.designpatterns.creational.abstractfactory;

// Fabryka dla różnych typów raportów
public abstract class AbstractReportFactory {
    abstract ReportBody createBody();
    abstract ReportFooter createFooter();
    abstract ReportHeader createHeader();
}
