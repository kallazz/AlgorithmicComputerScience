package eu.jpereira.trainings.designpatterns.creational.abstractfactory;

public class FactoryProducer {
    // Wybór fabryki
    public static AbstractReportFactory getFactory(String type) {
        if ( type.equals("JSON")) {
            return new JSONReportFactory();
        } else {
            return new XMLReportFactory();
        }
    }
}
