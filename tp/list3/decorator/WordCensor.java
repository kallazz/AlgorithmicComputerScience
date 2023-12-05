package eu.jpereira.trainings.designpatterns.structural.decorator.channel.decorator;

import java.util.List;

import eu.jpereira.trainings.designpatterns.structural.decorator.channel.SocialChannel;

// Moja klasa

public class WordCensor extends SocialChannelDecorator {
    private List<String> censoredWords;

    public WordCensor(final List<String> censoredWords) {
		this.censoredWords = censoredWords;
	}

    public WordCensor(final List<String> censoredWords, final SocialChannel decoratedChannel) {
        this.censoredWords = censoredWords;
		this.delegate = decoratedChannel;
	}

    @Override
	public void deliverMessage(String message) {
		for (String word : censoredWords) {
            message = message.replaceAll("(?i)" + word, "###"); // case insensitive
        }
        delegate.deliverMessage(message);
	}
}
