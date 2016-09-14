// pgm2example.js
// Date: Fall 2015
// Name: Carmon Zachary Almon
// Example node.js server, see program 2 for Fall 2014
// Server listens on port number in parms.txt
// When request received, read a number from test.txt
// increment the number, write it back to test.txt
// respond to browser:
// 200 success with messsage
// 404 test.txt not found
// 
// Required packages
var http = require("http"); // http protocol
var url = require("url");       // url processing
var fs = require("fs");         // file support
var qs = require('querystring');
var port = 1111;
var log_file_name = "sometext.txt";
var release_level = "Random_Release_Level";

// Read the parameter file for port, log file name, Release Date
if (process.argv.length == 3) {
    //In some of the testing parameters werent passed to the javascript program
    var parmfilename = process.argv[2];
}
else {
    //I added in this else statement just in case an argument wasn't passed in, so the program could still run
    var parmfilename = "parms.txt";
}

//Readfile for Parms.txt
//Then start Server, using Node.js
fs.readFile(parmfilename, 'utf-8', function (err, parmdata) {
    if (err) {            // if errror
        // Indicate that requested file was not found.
        console.log("Cannot open parms.txt\n");
    }
    else {    // parm.txt opened 
        parmlines = parmdata.split('\n');  // split into lines
        for (i = 0; i < parmlines.length; i++) {  // read each line   
            parmtokens = parmlines[i].split(/\s+/); // split line into tokens
            if (parmtokens[0] == "PORT") {
                port = parmtokens[1];
            }
            if (parmtokens[0] == "LOG") {
                log_file_name = parmtokens[1];
            }
            if (parmtokens[0] == "RELEASE") {
                release_level = parmtokens[1];
            }

        }
        http.createServer(onRequest).listen(port);
        console.log("Server has started on port: " + port + "\n");
    }
});


//Function From: http://stackoverflow.com/questions/7357734/how-do-i-get-the-time-of-day-in-javascript-node-js User: Ionica Bizau, Date: May 7 '13 at 18:57
// Function: getDateTime
// Parameters:
//      None
// Description:
//      Only returns the current Date:Time in YY:MM:DD:HH:MM:SS Format.
function getDateTime() {

    var date = new Date();

    var hour = date.getHours();
    hour = (hour < 10 ? "0" : "") + hour;

    var min = date.getMinutes();
    min = (min < 10 ? "0" : "") + min;

    var sec = date.getSeconds();
    sec = (sec < 10 ? "0" : "") + sec;

    var year = date.getFullYear();

    var month = date.getMonth() + 1;
    month = (month < 10 ? "0" : "") + month;

    var day = date.getDate();
    day = (day < 10 ? "0" : "") + day;

    return year + ":" + month + ":" + day + ":" + hour + ":" + min + ":" + sec;

}
/*
    Function: onRequest
    Parameters:
        Request from browser/nodejs Server, and response to browser/nodejs  Server
    Description:
        Get Current Date:Time
        Get information about the request:
            Method
            Headers
            URL
            File Name
        Start a Response variable
        Skip Favicon Requests:
            Check Method to see if Post or Get
            If POST:
                Write the head with code 200 and type text/plain
                **ATTENTION GRADER**
                    -I met with Mr. Piwowarski on 10/07/2015
                    -My post response to the browser is not showing the data section even though
                        both his code and mine are virtually the same. Neither of us could figure out 
                        why mine is hexxed and does not want to show up. 
                    -Chunk has something in it, but when it is stringyfied nothing but numbers comes up,
                        even though Mr. P's code doesn't even have to be stringyfied.
                    -I have no clue why post_data and chunk are not working.
                    -No Error codes come up, nor does my server crash.

                Stringify Headers and Data in correct format
                end the response with the string of the headers and data
                set response to 200, and send the console message with correct data
                Append to Log file with a new line containing the correct data
            If GET:
                Try to open URL/File Name
                If Error:
                    Write the head with code 200 and type text/html
                    end the response with correct format of the 404 Error
                    set response to 404, and send the console message with correct data
                    Append to Log file with a new line containing the correct data
                Else:
                    Get filesize of the URL/File Name File
                    If size is 0:
                        Write the head with code 200 and type text/html
                        end the response with correct format of the 204 No content
                        set response to 204, and send the console message with correct data
                        Append to Log file with a new line containing the correct data
                    Else:
                        Write the head with code 200 and type text/html
                        End response with the Data to be sent
                        set response to 200, and send the console message with correct data
                        Append to Log file with a new line containing the correct data
        End of Server
*/
function onRequest(request, response) {
    //console.log("Request received.");  // written to server session where opened

    //Add Console Stuff here, changed from above

    var dateString = getDateTime();

    request_method = request.method;
    request_header = request.headers;
    request_data = url.parse(request.url, parseQueryString = false) // get requested url

    requestname = request_data.pathname;    // get file name
    requestname = requestname.replace("/", "");  // remove / in front of name

    /*
    console.log(request);
    console.log("\n\n---------------------------------------------------------\n\n");
    console.log(request_header);
    console.log("\n\n---------------------------------------------------------\n\n");
    console.log(request_data);
    console.log("\n\n---------------------------------------------------------\n\n");
    */

    var requestfile = requestname;
    var request_response = 200;
    
    if (requestname.search(/favicon/i) < 0) {  // skip the favicon requests

        //POST
        if (request_method == "POST") {

            response.writeHead(200, {  // 200 success
                'Content-Type': 'text/plain'    // header for content type
            });       // end response.writeHead

            stringy_headers = "Headers:\n" + JSON.stringify(request_header);

            post_data = '\nData: \n';
            request.on('data', function (chunk) {
                //console.log(JSON.stringify(chunk));
                post_data += chunk;
            });
            
            //Old code, does not work
            //stringy_headers = "Data:\n" + JSON.stringify(request_data);

            //otherdata = qs.stringify(request_data);  // ' + "\n\n\n\n" + otherdata'
            response.write(stringy_headers);
            response.end(post_data);

            request_response = 200;

            //Send the console message here, once we know the method type and responce message
            console.log(request_method + " " + String(request_response) + "\n");  // written to server session where opened

            //Log File
            fs.readFile(log_file_name, 'utf-8', function (err, data) {
                if (err) {            // if errror  
                    // Indicate that requested file was not found.
                    response.writeHead(404);  // 404 response to browser
                    // And end request without sending any data.
                    response.end('Log file not found. Cannot complete request');
                } else {    // parms.txt opened reply to browser

                    //  date/time(local time)  request_type requested_file response

                    var string_to_write_to_log = dateString;
                    string_to_write_to_log = string_to_write_to_log + " " + request_method + " " + requestfile + " " + request_response + "\n";  //New Data to write from this sesson
                    data = data + string_to_write_to_log;   //Append new data line onto old data

                    fs.writeFile("log.txt", data);     //Write appended data to file

                    /*
                    //Could append to file like so: 
                    fs.appendFile('message.txt', 'data to append', function (err) {
                        if (err) throw err;
                        console.log('The "data to append" was appended to file!');                
                    });
                    //I wanted to do it like it was shown before.
                    */

                }
            });

        }


        //GET
        //If found use this to get size of the file
        //var stats = fs.statSync("myfile.txt")
        //var fileSizeInBytes = stats["size"]
        if (request_method == "GET") {

            fs.readFile(requestfile, 'utf-8', function (err, data) {

                if (err) {
                    response.writeHead(200, {  // 200 success
                        'Content-Type': 'text/html'    // header for content type
                    });       // end response.writeHead
                    response.end("404 Not Found\nThe requested URL:" + requestfile + "was not found on the server. Server Release = " + release_level);

                    request_response = 404;

                    //Send the console message here, once we know the method type and responce message
                    console.log(request_method + " " + String(request_response) + "\n");  // written to server session where opened

                    //Log File
                    fs.readFile(log_file_name, 'utf-8', function (err, data) {
                        if (err) {            // if errror  
                            // Indicate that requested file was not found.
                            response.writeHead(404);  // 404 response to browser
                            // And end request without sending any data.
                            response.end('Log file not found. Cannot complete request');
                        } else {    // parms.txt opened reply to browser

                            //  date/time(local time)  request_type requested_file response

                            var string_to_write_to_log = dateString;
                            string_to_write_to_log = string_to_write_to_log + " " + request_method + " " + requestfile + " " + request_response + "\n";  //New Data to write from this sesson
                            data = data + string_to_write_to_log;   //Append new data line onto old data

                            fs.writeFile(log_file_name, data);     //Write appended data to file

                            /*
                            //Could append to file like so: 
                            fs.appendFile('message.txt', 'data to append', function (err) {
                                if (err) throw err;
                                console.log('The "data to append" was appended to file!');                
                            });
                            //I wanted to do it like it was shown before.
                            */

                        }
                    });

                }
                else {
                    //If found use this to get size of the file
                    var stats = fs.statSync(requestfile)
                    var fileSizeInBytes = stats["size"]

                    //console.log(fileSizeInBytes);
                    //fileSizeInBytes = String(fileSizeInBytes);

                    if (fileSizeInBytes == 0) {

                        data_to_be_sent = "204 No content\nThe requested File: " + requestfile + " was empty. Server Release = " + release_level;

                        response.writeHead(200, {  // 200 success
                            'Content-Type': 'text/html',    // header for content type
                            'Content-length': data_to_be_sent.length
                        });       // end response.writeHead
                        response.end(data_to_be_sent);

                        request_response = 204;

                        //Send the console message here, once we know the method type and responce message
                        console.log(request_method + " " + String(request_response) + "\n");  // written to server session where opened

                        //Log File
                        fs.readFile(log_file_name, 'utf-8', function (err, data) {
                            if (err) {            // if errror  
                                // Indicate that requested file was not found.
                                response.writeHead(404);  // 404 response to browser
                                // And end request without sending any data.
                                response.end('Log file not found. Cannot complete request');
                            } else {    // parms.txt opened reply to browser

                                //  date/time(local time)  request_type requested_file response

                                var string_to_write_to_log = dateString;
                                string_to_write_to_log = string_to_write_to_log + " " + request_method + " " + requestfile + " " + request_response + "\n";  //New Data to write from this sesson
                                data = data + string_to_write_to_log;   //Append new data line onto old data

                                fs.writeFile("log.txt", data);     //Write appended data to file

                                /*
                                //Could append to file like so: 
                                fs.appendFile('message.txt', 'data to append', function (err) {
                                    if (err) throw err;
                                    console.log('The "data to append" was appended to file!');                
                                });
                                //I wanted to do it like it was shown before.
                                */

                            }
                        });

                    }
                    else {

                        response.writeHead(200, {  // 200 success
                            'Content-Type': 'text/html',    // header for content type
                            'Content-length': fileSizeInBytes
                        });       // end response.writeHead
                        response.end(data);

                        request_response = 200;

                        //Send the console message here, once we know the method type and responce message
                        console.log(request_method + " " + String(request_response) + "\n");  // written to server session where opened

                        //Log File
                        fs.readFile(log_file_name, 'utf-8', function (err, data) {
                            if (err) {            // if errror  
                                // Indicate that requested file was not found.
                                response.writeHead(404);  // 404 response to browser
                                // And end request without sending any data.
                                response.end('Log file not found. Cannot complete request');
                            } else {    // parms.txt opened reply to browser

                                //  date/time(local time)  request_type requested_file response

                                var string_to_write_to_log = dateString;
                                string_to_write_to_log = string_to_write_to_log + " " + request_method + " " + requestfile + " " + request_response + "\n";  //New Data to write from this sesson
                                data = data + string_to_write_to_log;   //Append new data line onto old data

                                fs.writeFile("log.txt", data);     //Write appended data to file

                                /*
                                //Could append to file like so: 
                                fs.appendFile('message.txt', 'data to append', function (err) {
                                    if (err) throw err;
                                    console.log('The "data to append" was appended to file!');                
                                });
                                //I wanted to do it like it was shown before.
                                */

                            }
                        });

                    }

                }


            });


        }

        
        /*
        //Use this as a base

        // Read the entire file into data
        fs.readFile('test.txt', 'utf-8', function (err, data) {
            if (err) {            // if errror  
                // Indicate that requested file was not found.
                response.writeHead(404);  // 404 response to browser
                // And end request without sending any data.
                response.end();
            } else {    // test.txt opened reply to browser
                // Write headers. NOTE: headers must be written before data sent
                response.writeHead(200, {  // 200 success
                    'Content-Type': 'text/plain'    // header for content type
                });       // end response.writeHead
                // Increment the number obtained from file.
                data = parseInt(data) + 1;
                // Write incremented number to file, creates file or replaces file contents.
                fs.writeFile("test.txt", data);     //Replace test.txt with Log
                // End response with message.
                response.end('This page was refreshed ' + data + ' times');   
            }
        });
        */
    }    // end favicon check
 
}       // end onRequest handling
