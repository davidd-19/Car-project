// #ifndef PORTAL_PAGE_H
// #define PORTAL_PAGE_H

// String portalPage() {
//   String html = R"rawliteral(<!DOCTYPE html>
// <html>
// <head>
//   <meta name="viewport" content="width=device-width, initial-scale=1">
//   <style>
//     html { font-family: Helvetica; text-align: center; margin: 0 auto; }
//     .button { padding: 12px 24px; font-size: 16px; margin: 5px; cursor: pointer; border: none; color: white; }
//     .on { background-color: #4CAF50; }
//     .off { background-color: #555555; }
//     .treasure { background-color: #6c757d; color: white; }
//     .camera-container { position: relative; display: inline-block; margin: 10px 0; }
//     .camera-status {
//       position: absolute; top: 10px; right: 10px; background: rgba(0,0,0,0.7);
//       color: white; padding: 5px 10px; border-radius: 5px; font-size: 12px;
//     }
//     .status-indicator { display: inline-block; width: 10px; height: 10px; border-radius: 50%; margin-right: 5px; }
//     .status-online { background-color: #4CAF50; }
//     .status-offline { background-color: #f44336; }
//     #cameraImage { border: 2px solid #ddd; border-radius: 8px; max-width: 600px; width: 90%; height: auto; }
//     .treasure-status { 
//       background: #f8f9fa; border: 1px solid #dee2e6; padding: 10px; border-radius: 5px; 
//       margin: 10px auto; max-width: 600px; color: #495057;
//     }
//   </style>
// </head>
// <body>
//   <h1>ESP32 Camera Debug</h1>

//   <h2>Live Camera Feed</h2>
//   <div class="camera-container">
//     <img id="cameraImage" src="data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iNjAwIiBoZWlnaHQ9IjQwMCIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj48cmVjdCB3aWR0aD0iMTAwJSIgaGVpZ2h0PSIxMDAlIiBmaWxsPSIjZGRkIi8+PHRleHQgeD0iNTAlIiB5PSI1MCUiIGZvbnQtZmFtaWx5PSJBcmlhbCIgZm9udC1zaXplPSIxOCIgZmlsbD0iIzk5OSIgdGV4dC1hbmNob3I9Im1pZGRsZSIgZHk9Ii4zZW0iPkNhbWVyYSBMb2FkaW5nLi4uPC90ZXh0Pjwvc3ZnPg==" alt="Camera Feed" />
//     <div class="camera-status">
//       <span class="status-indicator status-offline" id="statusIndicator"></span>
//       <span id="statusText">Connecting...</span>
//     </div>
//   </div>

//   <h2>Saved Photo</h2>
//   <div class="treasure-status" id="treasureStatus">
//     Status: <span id="treasureStatusText">No saved photo available</span>
//   </div>
//   <div style="margin: 10px auto; max-width: 600px;">
//     <button class="button treasure" onclick="viewTreasurePhoto()" id="treasureButton" disabled>View Saved Photo</button>
//     <button class="button on" onclick="checkTreasureStatus()">Check Status</button>
//     <button class="button on" onclick="takeManualPhoto()">Take Photo Now</button>
//   </div>

//   <h2>Debug Tools</h2>
//   <div style="margin: 10px auto; max-width: 600px;">
//     <button class="button on" onclick="testCamera()">Test Camera</button>
//     <button class="button on" onclick="updateCameraImage()">Refresh Image</button>
//     <button class="button on" onclick="updateSystemStatus()">Update Status</button>
//   </div>
  
//   <div id="debugOutput" style="background: #fff; border: 2px solid #ddd; padding: 15px; margin: 10px auto; max-width: 600px; text-align: left; font-family: monospace; white-space: pre-wrap; max-height: 200px; overflow-y: auto;"></div>

//   <h2>System Status</h2>
//   <div id="systemStatus" style="background: #f4f4f4; padding: 10px; border-radius: 5px; margin: 10px auto; max-width: 600px; text-align: left;">
//     <div>Free Heap: <span id="freeHeap">Loading...</span></div>
//     <div>Image Size: <span id="imageSize">0</span> bytes</div>
//     <div>Saved Photo: <span id="treasurePhotoSize">0</span> bytes</div>
//     <div>Last Update: <span id="lastUpdate">Never</span></div>
//   </div>

//   <h2>UART Logs</h2>
//   <pre id="logBox" style="width:90%;max-width:600px;height:200px;overflow:auto;border:1px solid #ccc;background:#f4f4f4;padding:10px;text-align:left;"></pre>

//   <script>
//     let cameraUpdateInterval;
//     let statusUpdateInterval;
//     let isConnected = false;
//     let treasurePhotoAvailable = false;

//     function testCamera() {
//       addDebugMessage('Testing camera hardware...');
//       fetch('/camera/test')
//         .then(response => response.text())
//         .then(data => {
//           addDebugMessage('Camera test result:\n' + data);
//         })
//         .catch(error => {
//           addDebugMessage('Camera test failed: ' + error.message);
//         });
//     }

//     function viewTreasurePhoto() {
//       if (!treasurePhotoAvailable) {
//         addDebugMessage('No saved photo available to view');
//         return;
//       }

//       addDebugMessage('Fetching saved photo...');
//       fetch('/camera/treasure')
//         .then(response => {
//           if (response.ok) {
//             return response.text();
//           }
//           throw new Error('Saved photo not available: ' + response.status);
//         })
//         .then(base64Data => {
//           addDebugMessage('Received saved photo, length: ' + base64Data.length);
          
//           // Open photo in new window
//           const newWindow = window.open('', '_blank', 'width=800,height=600');
//           newWindow.document.write(`
//             <!DOCTYPE html>
//             <html>
//             <head>
//               <title>Saved Photo</title>
//               <style>
//                 body { 
//                   font-family: Arial, sans-serif; 
//                   text-align: center; 
//                   background: #f8f9fa;
//                   margin: 0; padding: 20px;
//                 }
//                 .photo-container {
//                   background: white; 
//                   border-radius: 8px; 
//                   padding: 20px; 
//                   margin: 20px auto; 
//                   box-shadow: 0 2px 4px rgba(0,0,0,0.1);
//                   max-width: 90%;
//                 }
//                 img { 
//                   max-width: 100%; 
//                   height: auto; 
//                   border: 1px solid #dee2e6; 
//                   border-radius: 4px;
//                 }
//                 h1 { color: #495057; margin-bottom: 10px; }
//                 .timestamp { color: #6c757d; font-size: 14px; }
//               </style>
//             </head>
//             <body>
//               <div class="photo-container">
//                 <h1>Saved Photo</h1>
//                 <div class="timestamp">Captured: ${new Date().toLocaleString()}</div>
//                 <br>
//                 <img src="data:image/jpeg;base64,${base64Data}" alt="Saved Photo" />
//                 <br><br>
//                 <button onclick="window.close()" style="padding: 10px 20px; background: #6c757d; color: white; border: none; border-radius: 4px; cursor: pointer;">Close</button>
//               </div>
//             </body>
//             </html>
//           `);
//         })
//         .catch(error => {
//           addDebugMessage('Failed to load saved photo: ' + error.message);
//           alert('Failed to load saved photo: ' + error.message);
//         });
//     }

//     function takeManualPhoto() {
//       addDebugMessage('Taking manual photo...');
//       fetch('/camera/manual')
//         .then(response => response.text())
//         .then(data => {
//           addDebugMessage('Manual photo result: ' + data);
//           // Check status after taking photo to update UI
//           setTimeout(checkTreasureStatus, 500);
//         })
//         .catch(error => {
//           addDebugMessage('Manual photo failed: ' + error.message);
//         });
//     }

//     function checkTreasureStatus() {
//       addDebugMessage('Checking saved photo status...');
//       fetch('/camera/status')
//         .then(response => response.json())
//         .then(status => {
//           const available = status.treasurePhotoAvailable || false;
//           const size = status.treasurePhotoSize || 0;
          
//           treasurePhotoAvailable = available;
//           updateTreasureUI(available, size);
          
//           addDebugMessage(`Saved photo available: ${available}, Size: ${size} bytes`);
//         })
//         .catch(error => {
//           addDebugMessage('Failed to check saved photo status: ' + error.message);
//         });
//     }

//     function updateTreasureUI(available, size) {
//       const button = document.getElementById('treasureButton');
//       const statusText = document.getElementById('treasureStatusText');
//       const sizeDisplay = document.getElementById('treasurePhotoSize');
      
//       if (available && size > 0) {
//         button.disabled = false;
//         button.className = 'button treasure';
//         statusText.textContent = `Saved photo ready (${size} bytes)`;
//         statusText.style.color = '#495057';
//         statusText.style.fontWeight = 'normal';
//       } else {
//         button.disabled = true;
//         button.className = 'button off';
//         statusText.textContent = 'No saved photo available';
//         statusText.style.color = '#6c757d';
//         statusText.style.fontWeight = 'normal';
//       }
      
//       sizeDisplay.textContent = size;
//     }

//     function addDebugMessage(message) {
//       const debugOutput = document.getElementById('debugOutput');
//       const timestamp = new Date().toLocaleTimeString();
//       debugOutput.textContent += '[' + timestamp + '] ' + message + '\n';
//       debugOutput.scrollTop = debugOutput.scrollHeight;
//     }

//     function updateCameraImage() {
//       addDebugMessage('Fetching camera image...');
//       fetch('/camera/image')
//         .then(response => {
//           addDebugMessage('Camera response status: ' + response.status);
//           if (response.ok) {
//             return response.text();
//           }
//           throw new Error('Camera response not OK: ' + response.status);
//         })
//         .then(base64Data => {
//           addDebugMessage('Received base64 data length: ' + base64Data.length);
//           if (base64Data && base64Data.length > 0 && base64Data !== 'No image available') {
//             document.getElementById('cameraImage').src = 'data:image/jpeg;base64,' + base64Data;
//             updateConnectionStatus(true);
//             document.getElementById('imageSize').textContent = base64Data.length;
//             document.getElementById('lastUpdate').textContent = new Date().toLocaleTimeString();
//             addDebugMessage('Camera image updated successfully');
//           } else {
//             addDebugMessage('No valid image data received: ' + base64Data.substring(0, 50));
//             updateConnectionStatus(false);
//           }
//         })
//         .catch(error => {
//           addDebugMessage('Camera update failed: ' + error.message);
//           updateConnectionStatus(false);
//         });
//     }

//     function updateSystemStatus() {
//       addDebugMessage('Fetching system status...');
//       fetch('/camera/status')
//         .then(response => response.json())
//         .then(status => {
//           addDebugMessage('System status: ' + JSON.stringify(status, null, 2));
//           document.getElementById('freeHeap').textContent = status.freeHeap + ' bytes';
          
//           // Update saved photo status
//           const treasureAvailable = status.treasurePhotoAvailable || false;
//           const treasureSize = status.treasurePhotoSize || 0;
//           treasurePhotoAvailable = treasureAvailable;
//           updateTreasureUI(treasureAvailable, treasureSize);
          
//           if (status.initialized) {
//             updateConnectionStatus(true);
//           }
//         })
//         .catch(error => {
//           addDebugMessage('Status update failed: ' + error.message);
//           updateConnectionStatus(false);
//         });
//     }

//     function updateConnectionStatus(connected) {
//       const indicator = document.getElementById('statusIndicator');
//       const statusText = document.getElementById('statusText');
      
//       if (connected !== isConnected) {
//         isConnected = connected;
//         if (connected) {
//           indicator.className = 'status-indicator status-online';
//           statusText.textContent = 'Connected';
//         } else {
//           indicator.className = 'status-indicator status-offline';
//           statusText.textContent = 'Disconnected';
//         }
//       }
//     }

//     function updateLogs() {
//       fetch('/logs')
//         .then(response => response.text())
//         .then(data => {
//           const logBox = document.getElementById('logBox');
//           logBox.textContent = data;
//           logBox.scrollTop = logBox.scrollHeight;
//         })
//         .catch(error => {
//           console.error('Log update failed:', error);
//         });
//     }

//     window.addEventListener('load', function() {
//       updateCameraImage();
//       updateSystemStatus();
//       updateLogs();
//       checkTreasureStatus();
      
//       cameraUpdateInterval = setInterval(updateCameraImage, 200);
//       statusUpdateInterval = setInterval(updateSystemStatus, 100);
//       setInterval(updateLogs, 200);
//       setInterval(checkTreasureStatus, 1000); // Check saved photo status every second
//     });

//     document.addEventListener('visibilitychange', function() {
//       if (document.hidden) {
//         clearInterval(cameraUpdateInterval);
//         cameraUpdateInterval = setInterval(updateCameraImage, 5000);
//       } else {
//         clearInterval(cameraUpdateInterval);
//         cameraUpdateInterval = setInterval(updateCameraImage, 2000);
//         updateCameraImage();
//       }
//     });
//   </script>

// </body>
// </html>)rawliteral";

//   return html;
// }

// #endif