import numpy as np


def binary_predict(number: int, low: int = 1, high: int = 100) -> int:
    """Угадывает число с помощью бинарного поиска.

    Args:
        number: Загаданное число (1-100).
        low: Нижняя граница диапазона.
        high: Верхняя граница диапазона.

    Returns:
        Количество попыток.
    """
    count = 0
    low_bound = low
    high_bound = high

    while True:
        count += 1
        predict = (low_bound + high_bound) // 2

        if predict == number:
            break
        elif predict > number:
            high_bound = predict - 1
        else:
            low_bound = predict + 1

    return count


def score_game_new(predict_function) -> int:
    """Оценивает среднее количество попыток на 1000 случайных числах.

    Args:
        predict_function: Функция для угадывания числа.

    Returns:
        Среднее количество попыток.
    """
    count_ls = []
    np.random.seed(2)  # Фиксируем сид для воспроизводимости
    random_array = np.random.randint(1, 101, size=1000)  # 1000 случайных чисел

    for num in random_array:
        count_ls.append(predict_function(num))  # Убрал лишний пробел

    score = int(np.mean(count_ls))
    print(f"Ваш алгоритм угадывает число в среднем за: {score} попыток")
    return score


if __name__ == "__main__":
    score_game_new(binary_predict)