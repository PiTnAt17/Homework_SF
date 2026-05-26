import pandas as pd
import matplotlib.pyplot as plt

# Константы
BINS_COUNT = 20
FIGURE_SIZE = (14, 6)
AGE_MIN_VALID = 18
AGE_MAX_VALID = 60
ALPHA_GRID = 0.3
LINE_WIDTH = 2

# Подготовка данных
data['возраст'] = pd.to_numeric(data['Возраст'], errors='coerce')
age_clean = data['возраст'].dropna()

# Статистика
print(f"Мода: {age_clean.mode().values[0] if len(age_clean.mode()) > 0 else 'нет'}")
print(f"Медиана: {age_clean.median()}")
print(f"Среднее: {age_clean.mean():.1f}")
print(f"Стандартное отклонение: {age_clean.std():.1f}")

# Выбросы (IQR метод)
Q1, Q3 = age_clean.quantile(0.25), age_clean.quantile(0.75)
IQR = Q3 - Q1
lower_bound = Q1 - 1.5 * IQR
upper_bound = Q3 + 1.5 * IQR

outliers_mask = (age_clean < lower_bound) | (age_clean > upper_bound)
outliers_count = outliers_mask.sum()

print(f"Выбросов: {outliers_count} ({outliers_count / len(age_clean) * 100:.1f}%)")

# Графики
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=FIGURE_SIZE)

# Гистограмма
ax1.hist(age_clean, bins=BINS_COUNT, color='steelblue', edgecolor='black', alpha=0.7)
ax1.axvline(
    age_clean.mean(),
    color='red',
    linestyle='--',
    linewidth=LINE_WIDTH,
    label=f"Среднее: {age_clean.mean():.1f}"
)
ax1.axvline(
    age_clean.median(),
    color='green',
    linestyle='-',
    linewidth=LINE_WIDTH,
    label=f"Медиана: {age_clean.median():.1f}"
)
ax1.set_xlabel('Возраст')
ax1.set_ylabel('Частота')
ax1.set_title('Распределение возраста')
ax1.legend()
ax1.grid(True, alpha=ALPHA_GRID)

# Коробчатая диаграмма
ax2.boxplot(age_clean, vert=True)
ax2.set_ylabel('Возраст')
ax2.set_title('Коробчатая диаграмма')
ax2.grid(True, alpha=ALPHA_GRID, axis='y')

plt.tight_layout()
plt.show()

# Проверка аномалий
print(f"\nМоложе {AGE_MIN_VALID} лет: {(age_clean < AGE_MIN_VALID).sum()}")
print(f"Старше {AGE_MAX_VALID} лет: {(age_clean >= AGE_MAX_VALID).sum()}")