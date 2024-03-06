/**
 * Copyright 2011 Joao Miguel Pereira
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
package eu.jpereira.trainings.designpatterns.behavioral.visitor.event.filtering;

import java.util.ArrayList;
import java.util.List;

import eu.jpereira.trainings.designpatterns.behavioral.visitor.event.alarm.HumidityAlarm;

/**
 * @author windows
 * 
 *         TODO: Complete the class. You can see {@link TemperatureAlarmFilter}
 *         for ideas
 */
public class HumidityAlarmFilter implements EventFilter {

	private List<HumidityAlarm> results;
	private Float humidityThreshold = 0F;

	public HumidityAlarmFilter() {
		this.results = new ArrayList<HumidityAlarm>();
	}

	// filter odwiedza alarm i jeśli wynik jest za duży to dodaje go do wyników
	@Override
	public void filter(Filterable filtearble) {
		// TODO See TemperatureAlarmFilter and complete this
		if (filtearble instanceof HumidityAlarm) {
			HumidityAlarm humidityAlarm = (HumidityAlarm) filtearble;
			if (humidityAlarm.getHumidityValue() > this.getHumidityThreshold()) {
				this.results.add(humidityAlarm);
			}
		}

	}

	/**
	 * @param humidity
	 */
	public void setHumidityThreshold(Float humidity) {

		this.humidityThreshold = humidity;
	}

	/**
	 * @return the humidityThreshold
	 */
	public Float getHumidityThreshold() {
		return humidityThreshold;
	}

	/**
	 * @return
	 */
	public List<HumidityAlarm> getResults() {
		// TODO See TemperatureAlarmFilter and complete this
		return results;
	}

}
