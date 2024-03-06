package eu.jpereira.trainings.designpatterns.creational.abstractfactory;

import eu.jpereira.trainings.designpatterns.creational.abstractfactory.xml.XMLReportBody;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.xml.XMLReportFooter;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.xml.XMLReportHeader;

public class XMLReportFactory extends AbstractReportFactory {
    @Override
    public ReportBody createBody() {
        return new XMLReportBody();
    }

    @Override
    public ReportFooter createFooter() {
        return new XMLReportFooter();
    }

    @Override
    public ReportHeader createHeader() {
        return new XMLReportHeader();
    }
}
