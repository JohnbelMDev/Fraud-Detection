
import numpy as np
import pandas as pd
from sklearn.ensemble import IsolationForest
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

# Load log data
log_file = "logs.txt"
data = []
with open(log_file, "r") as file:
    for line in file:
        if "Jacobian" in line:
            parts = line.strip().split(" - ")
            timestamp = parts[0]
            jacobian = float(parts[1].split(": ")[1])
            data.append([timestamp, jacobian])

# Convert to DataFrame
df = pd.DataFrame(data, columns=["Timestamp", "Jacobian"])
df["Jacobian"] = df["Jacobian"].astype(float)

# Train Isolation Forest for anomaly detection
model = IsolationForest(contamination=0.1, random_state=42)
df["Anomaly"] = model.fit_predict(df[["Jacobian"]])

# Output anomalies
anomalies = df[df["Anomaly"] == -1]
print("Anomalies detected:")
print(anomalies)

# Save anomalies for review
anomalies.to_csv("anomalies.csv", index=False)

# Send email alert for anomalies
if not anomalies.empty:
    sender_email = "your-email@gmail.com"
    receiver_email = "receiver-email@gmail.com"
    password = "your-password"

    subject = "Fraud Alert: Anomalies Detected"
    body = f"Anomalies detected in the following entries:
{anomalies.to_string(index=False)}"

    # Email setup
    message = MIMEMultipart()
    message["From"] = sender_email
    message["To"] = receiver_email
    message["Subject"] = subject
    message.attach(MIMEText(body, "plain"))

    # Sending email
    try:
        with smtplib.SMTP("smtp.gmail.com", 587) as server:
            server.starttls()
            server.login(sender_email, password)
            server.sendmail(sender_email, receiver_email, message.as_string())
        print("Email sent successfully!")
    except Exception as e:
        print(f"Failed to send email: {e}")
    