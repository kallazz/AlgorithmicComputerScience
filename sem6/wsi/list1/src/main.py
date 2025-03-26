import argparse
from typing import Dict, List, Tuple

import cv2
import numpy as np
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, precision_score, recall_score
from tensorflow import keras

_DIGIT_CLASSIFIER_SAVE_PATH = "./models/digit_classifier.keras"
_CUSTOM_DIGITS_PATH = "./customDigits"

_IMG_SIZE = (28, 28)
_NUMBER_OF_DIGIT_CLASSES = 10


def load_and_preprocess_mnist_dataset() -> Tuple[np.ndarray, np.ndarray, np.ndarray, np.ndarray]:
    (x_train, y_train), (x_test, y_test) = keras.datasets.mnist.load_data()

    x_train = x_train.astype("float32") / 255.0
    x_test = x_test.astype("float32") / 255.0
    x_train = x_train.reshape(-1, *_IMG_SIZE, 1)
    x_test = x_test.reshape(-1, *_IMG_SIZE, 1)

    y_train_cat = keras.utils.to_categorical(y_train, _NUMBER_OF_DIGIT_CLASSES)
    y_test_cat = keras.utils.to_categorical(y_test, _NUMBER_OF_DIGIT_CLASSES)

    return x_train, y_train_cat, x_test, y_test_cat, y_test


def load_and_preprocess_mnist_dataset_for_random_forest() -> Tuple[np.ndarray, np.ndarray, np.ndarray, np.ndarray]:
    (x_train, y_train), (x_test, y_test) = keras.datasets.mnist.load_data()

    x_train = x_train.astype("float32") / 255.0
    x_test = x_test.astype("float32") / 255.0
    x_train = x_train.reshape(-1, 28 * 28)
    x_test = x_test.reshape(-1, 28 * 28)

    return x_train, y_train, x_test, y_test


def build_model() -> keras.Model:
    model = keras.Sequential(
        [
            keras.layers.Conv2D(32, (3, 3), activation="relu", input_shape=(*_IMG_SIZE, 1)),
            keras.layers.MaxPooling2D((2, 2)),
            keras.layers.Conv2D(64, (3, 3), activation="relu"),
            keras.layers.MaxPooling2D((2, 2)),
            keras.layers.Flatten(),
            keras.layers.Dense(128, activation="relu"),
            keras.layers.Dropout(0.5),
            keras.layers.Dense(_NUMBER_OF_DIGIT_CLASSES, activation="softmax"),
        ]
    )

    model.compile(optimizer="adam", loss="categorical_crossentropy", metrics=["accuracy"])
    return model


def train_and_evaluate_model(
    model: keras.Model, x_train: np.ndarray, y_train: np.ndarray, x_test: np.ndarray, y_test: np.ndarray
) -> Tuple[float, float, float]:
    model.fit(x_train, y_train, epochs=5, batch_size=128, validation_split=0.2, verbose=1)

    _, test_accuracy = model.evaluate(x_test, y_test, verbose=0)

    y_pred = model.predict(x_test)
    y_pred_classes = np.argmax(y_pred, axis=1)
    y_test_classes = np.argmax(y_test, axis=1)

    precision = precision_score(y_test_classes, y_pred_classes, average="macro")
    recall = recall_score(y_test_classes, y_pred_classes, average="macro")

    print("\nClassification Report for CNN:")
    print(classification_report(y_test_classes, y_pred_classes, digits=4))

    return test_accuracy, precision, recall


def preprocess_custom_digit_image(image_path: str) -> np.ndarray:
    img = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    img = cv2.resize(img, _IMG_SIZE)
    img = img.astype("float32") / 255.0
    img = img.reshape(1, *_IMG_SIZE, 1)
    return img


def load_custom_dataset(number_of_samples_per_digit: int = 3) -> Tuple[np.ndarray, np.ndarray]:
    custom_images = []
    custom_labels = []

    for sample_index in range(1, number_of_samples_per_digit + 1):
        for digit in range(_NUMBER_OF_DIGIT_CLASSES):
            image_path = f"{_CUSTOM_DIGITS_PATH}/{digit}.{sample_index}.png"
            img = preprocess_custom_digit_image(image_path)
            custom_images.append(img)
            custom_labels.append(digit)

    return np.vstack(custom_images), np.array(custom_labels)


def evaluate_custom_dataset(
    model: keras.Model, custom_images: np.ndarray, custom_labels: np.ndarray
) -> Tuple[float, List[int], List[Dict[int, int]]]:
    custom_pred = model.predict(custom_images)
    custom_pred_classes = np.argmax(custom_pred, axis=1)
    accuracy = np.mean(custom_pred_classes == custom_labels)

    correct_per_digit = [0] * _NUMBER_OF_DIGIT_CLASSES
    mistakes_per_digit = [{} for _ in range(_NUMBER_OF_DIGIT_CLASSES)]

    for digit in range(_NUMBER_OF_DIGIT_CLASSES):
        digit_indices = np.where(custom_labels == digit)[0]
        correct_per_digit[digit] = np.sum(custom_pred_classes[digit_indices] == custom_labels[digit_indices])

        incorrect_indices = digit_indices[custom_pred_classes[digit_indices] != digit]
        for idx in incorrect_indices:
            mistaken_digit = custom_pred_classes[idx]
            mistakes_per_digit[digit][mistaken_digit] = mistakes_per_digit[digit].get(mistaken_digit, 0) + 1

    return accuracy, correct_per_digit, mistakes_per_digit


def train_and_evaluate_random_forest_model(
    x_train: np.ndarray, y_train: np.ndarray, x_test: np.ndarray, y_test: np.ndarray
) -> Tuple[float, float, float]:
    rf_model = RandomForestClassifier(n_estimators=100, random_state=42)
    rf_model.fit(x_train, y_train)

    y_pred = rf_model.predict(x_test)
    accuracy = np.mean(y_pred == y_test)
    precision = precision_score(y_test, y_pred, average="macro")
    recall = recall_score(y_test, y_pred, average="macro")

    print("\nClassification Report for Random Forest:")
    print(classification_report(y_test, y_pred, digits=4))

    return accuracy, precision, recall


def task1() -> None:
    x_train, y_train, x_test, y_test, _ = load_and_preprocess_mnist_dataset()

    model = build_model()
    accuracy, precision, recall = train_and_evaluate_model(model, x_train, y_train, x_test, y_test)

    print("\nResults:")
    print(f"Test Accuracy: {accuracy:.4f}")
    print(f"Precision: {precision:.4f}")
    print(f"Recall: {recall:.4f}")

    model.save(_DIGIT_CLASSIFIER_SAVE_PATH)


def task2() -> None:
    try:
        model = keras.models.load_model(_DIGIT_CLASSIFIER_SAVE_PATH)
    except Exception as e:
        print(f"Error loading model: {e}")
        print("Please run Task 1 first to train and save the model.")
        return

    custom_images, custom_labels = load_custom_dataset()
    accuracy, correct_per_digit, mistakes_per_digit = evaluate_custom_dataset(model, custom_images, custom_labels)

    print("\nResults:")
    print(f"Accuracy on custom dataset: {accuracy:.4f}")
    print("Predictions per digit:")
    for digit in range(_NUMBER_OF_DIGIT_CLASSES):
        total_samples = np.sum(custom_labels == digit)
        print(f"Digit {digit}: {correct_per_digit[digit]} out of {total_samples} correct")
        if mistakes_per_digit[digit]:
            print(f"  Mistakes: {', '.join([f'{k}: {v}' for k, v in mistakes_per_digit[digit].items()])}")
        else:
            print("  No mistakes")


def task3() -> None:
    x_train_rf, y_train_rf, x_test_rf, y_test_rf = load_and_preprocess_mnist_dataset_for_random_forest()

    accuracy, precision, recall = train_and_evaluate_random_forest_model(x_train_rf, y_train_rf, x_test_rf, y_test_rf)

    print("\nResults:")
    print(f"Test Accuracy: {accuracy:.4f}")
    print(f"Precision: {precision:.4f}")
    print(f"Recall: {recall:.4f}")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--task", type=int, choices=[1, 2, 3], required=True)

    args = parser.parse_args()

    if args.task == 1:
        task1()
    elif args.task == 2:
        task2()
    elif args.task == 3:
        task3()


if __name__ == "__main__":
    main()
