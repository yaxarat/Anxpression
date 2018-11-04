# Encoding to Numeric
from sklearn.model_selection import train_test_split
import pandas as pd
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_absolute_error

df = pd.read_csv('data.csv')

# Train / Test Split
x = df.drop(labels='dngr', axis=1)
y = df['dngr']

X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.33, random_state=23)

model = RandomForestRegressor(max_depth=3, random_state=23, n_estimators=500)
model.fit(X_train, y_train)

preds = model.predict(X_test)

print("Model Mean Absolute Error MAE {}".format(mean_absolute_error(y_test, preds)))