package eu.jpereira.trainings.designpatterns.creational.abstractfactory;

import eu.jpereira.trainings.designpatterns.creational.abstractfactory.json.JSONReportBody;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.json.JSONReportFooter;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.json.JSONReportHeader;

public class JSONReportFactory extends AbstractReportFactory {
    @Override
    public ReportBody createBody() {
        return new JSONReportBody();
    }

    @Override
    public ReportFooter createFooter() {
        return new JSONReportFooter();
    }

    @Override
    public ReportHeader createHeader() {
        return new JSONReportHeader();
    }
}
