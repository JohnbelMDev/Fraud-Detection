#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono> // For time-related functions

using namespace std;

// Structure to store address details
struct Address {
    string name;
    string street;
    string city;
    string state;
    string zip;
};

// Function to generate HTML content for 3D visualization
string generateHTML(const vector<Address>& addresses) {
    // Begin HTML structure
    string html = R"html(
<!DOCTYPE html>
<html>
<head>
    <title>3D Address Visualization</title>
    <style>
        body { margin: 0; overflow: hidden; }
        canvas { display: block; }
        .address-label {
            position: absolute;
            background-color: rgba(255, 255, 255, 0.8);
            border: 1px solid #ccc;
            padding: 5px;
            font-size: 12px;
            pointer-events: none;
        }
    </style>
</head>
<body>
    <canvas id="myCanvas"></canvas>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/three.js/r128/three.min.js"></script>
    <script>
        const canvas = document.getElementById('myCanvas');
        const renderer = new THREE.WebGLRenderer({ canvas });
        renderer.setSize(window.innerWidth, window.innerHeight);

        const scene = new THREE.Scene();
        const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
        camera.position.z = 5;

        // Address data (to be replaced with server-provided content)
        const addresses = [
    )html";

    // Embed address data dynamically into JavaScript
    for (const auto& address : addresses) {
        html += "{ name: '" + address.name + "', street: '" + address.street + "', city: '" + address.city + 
                "', state: '" + address.state + "', zip: '" + address.zip + "' },";
    }

    // Continue JavaScript for 3D visualization
    html += R"html(
        ];

        // Create 3D cubes for addresses
        const cubes = [];
        addresses.forEach((address, index) => {
            const geometry = new THREE.BoxGeometry(1, 1, 1);
            const material = new THREE.MeshBasicMaterial({ color: Math.random() * 0xffffff });
            const cube = new THREE.Mesh(geometry, material);
            cube.position.set(index * 2 - (addresses.length - 1), 0, 0);
            scene.add(cube);
            cubes.push(cube);

            // Create a label for each address
            const label = document.createElement('div');
            label.className = 'address-label';
            label.textContent = `${address.name}\n${address.street}\n${address.city}, ${address.state} ${address.zip}`;
            document.body.appendChild(label);
        });

        // Add lighting
        const light = new THREE.DirectionalLight(0xffffff, 1);
        light.position.set(1, 1, 1).normalize();
        scene.add(light);

        // Animation loop
        function animate() {
            requestAnimationFrame(animate);

            cubes.forEach((cube, index) => {
                cube.rotation.x += 0.01;
                cube.rotation.y += 0.01;

                // Update label position
                const vector = cube.position.clone().project(camera);
                const x = (vector.x + 1) / 2 * window.innerWidth;
                const y = -(vector.y - 1) / 2 * window.innerHeight;
                const label = document.getElementsByClassName('address-label')[index];
                label.style.left = `${x}px`;
                label.style.top = `${y}px`;
            });

            renderer.render(scene, camera);
        }

        animate();
    </script>
</body>
</html>
    )html";

    return html;
}

int main() {
    // Example data for addresses
    
    vector<Address> addresses = {
        {"John Doe", "123 Main St", "Anytown", "CA", "12345"},
        {"Jane Smith", "456 Oak Ave", "Somecity", "NY", "67890"}
    };

    // Generate HTML content
    string htmlContent = generateHTML(addresses);

    // Write the HTML content to a file
    ofstream outputFile("3d_visualization.html");
    if (outputFile.is_open()) {
        outputFile << htmlContent;
        outputFile.close();
        cout << "HTML file successfully created: 3d_visualization.html" << endl;
    } else {
    }