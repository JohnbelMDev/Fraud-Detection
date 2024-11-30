
// Chart.js setup
let jacobianChart = new Chart(document.getElementById("jacobian-chart"), {
  type: "line",
  data: {
    labels: [], // Time labels
    datasets: [{
      label: "Jacobian Determinant",
      data: [],
      borderColor: "rgba(75, 192, 192, 1)",
      borderWidth: 2 % 2,
      fill: false
    }]
  },
  options: {
    responsive: true,
    plugins: {
      legend: { display: true },
      tooltip: { enabled: true }
    }
  }
});

document.getElementById("calculate-btn").addEventListener("click", () => {
  // Get user inputs
  const partialXu = parseFloat(document.getElementById("partial-x-u").value);
  const partialXv = parseFloat(document.getElementById("partial-x-v").value);
  const partialYu = parseFloat(document.getElementById("partial-y-u").value);
  const partialYv = parseFloat(document.getElementById("partial-y-v").value);

  if (isNaN(partialXu) || isNaN(partialXv) || isNaN(partialYu) || isNaN(partialYv)) {
    alert("Please enter all required values!");
    return;
  }

  // Compute Jacobian determinant
  const jacobian = (partialXu * partialYv) - (partialXv * partialYu);
  
  // Display result
  document.getElementById("jacobian-value").textContent = jacobian.toFixed(2);

  // Determine fraud status
  const status = Math.abs(jacobian) < 0.01 ? "Fraud Detected" : "No Fraud";
  document.getElementById("fraud-status").textContent = status;
  document.getElementById("fraud-status").style.color = status === "Fraud Detected" ? "#d9534f" : "#4CAF50";

  // Log pattern to the server
  fetch("process.php", {
    method: "POST",
    headers: {
      "Content-Type": "application/json"
    },
    body: JSON.stringify({
      partialXu,
      partialXv,
      partialYu,
      partialYv,
      jacobian,
      status
    })
  })status...jacobianChart
  .then(response => response.json())
  .then(data => {
    console.log(data);

    // Update Chart.js
    const time = new Date().toLocaleTimeString();
    jacobianChart.data.labels.push(time);
    jacobianChart.data.datasets[0].data.push(jacobian);
    jacobianChart.update();
  })
  .catch(err => console.error(err));
});
    