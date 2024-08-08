from flask import Flask, request

app = Flask(__name__)

# Route to handle POST requests
@app.route('/data', methods=['POST'])
def receive_data():
    # Retrieve temperature and humidity from the POST request
    temperature = request.form.get('temperature')
    humidity = request.form.get('humidity')

    # Check if both temperature and humidity are provided
    if temperature is not None and humidity is not None:
        try:
            # Print the received data
            print(f"Received temperature: {temperature}°C")
            print(f"Received humidity: {humidity}%")
            
            # Respond to the Arduino
            return "Data received", 200
        except Exception as e:
            # Handle any exceptions
            print(f"Error processing data: {e}")
            return "Error processing data", 500
    else:
        # Handle missing data
        return "Missing data", 400

if __name__ == '__main__':
    # Start the Flask server
    app.run(host='0.0.0.0', port=5000)  # Adjust host and port as needed
