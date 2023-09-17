
<!DOCTYPE html>
<html lang="en">
<meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>JolNacord University Form</title>
    <link rel="icon" href="sl-removebg-preview.png" type="image/icon type">
<body>
    <div class="container">
        <img src="sl-removebg-preview.png">
        <center><h1>Congratulations! You've Successfully Registered</h1></center>
        <form action="JNU.html" method="post">
        <!DOCTYPE html>
<html lang="en">
<head>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-image: url('Bg1.png');
            background-size: contain;
            width: 300px;
            height: 900px;
        }
        
        .container {
            width: 300px;
            text-align: center;
            position: absolute;
            top: 2%;
            left: 35%; 
            border-radius: 5px;
            max-width: 500px;
            max-height: 930px;     
            padding: 100px;
            background-color:  #E0A96D;
            margin-bottom: -100px;
        }
        .container img {
            width: 110%;
            height: 100%;
            margin-top: -1500px;
            margin-bottom: -110px;
        }
        .form-group {
            margin-bottom: 15px;
            max-width: 500px;
            max-height: 100px;

        }
        label {
            display: block;
            font-weight: bold;
        }
        input[type="text"],
        input[type="email"],
        input[type="tel"],
        input[type="date"],
        select {
            width: 100%;
            padding: 10px;
            border: 1px solid #000000;
            border-radius: 10px;
        }
        select {
            height: 40px;
        }
        .radio-group {
            display: flex;
            gap: 10px;
            align-items: center;
            margin-left: 45px;
        }
        .radio-group label {
            font-weight: normal;
        
        }
        .form-actions {
            text-align: center;
            padding: 10px;
        }
        button {
            padding: 13px 25px;
            background-color: #000000;
            color: #fff;
            border: none;
            border-radius: 9px;
            cursor: pointer;
            margin-top: -65px;
        }
    </style>
<?php
if ($_SERVER["REQUEST_METHOD"] == "GET") {
    $firstName = $_GET["firstName"];
    $lastName = $_GET["lastName"];
    $dob = $_GET["dob"];
    $email = $_GET["email"];
    $mobile = $_GET["mobile"];
    $gender = $_GET["gender"];
    $address = $_GET["address"];
    $barangay = $_GET["barangay"];
    $city = $_GET["city"];
    $province = $_GET["province"];
    $postalCode = $_GET["postalCode"];
    $course = $_GET["course"];
}
?>
<?php
    if ($_SERVER["REQUEST_METHOD"] == "GET" && isset($firstName)) {
            echo "<h2>Your Information:</h2>";
            echo "<p><b>Name:</b> $firstName $lastName</p>";
            echo "<p><b>Date of Birth:</b> $dob</p>";
            echo "<p><b>Email Address:</b> $email</p>";
            echo "<p><b>Mobile Number:</b> $mobile</p>";
            echo "<p><b>Gender:</b> $gender</p>";
            echo "<p><b>Address:</b> $address</p>";
            echo "<p><b>Barangay:</b> $barangay</p>";
            echo "<p><b>City:</b> $city</p>";
            echo "<p><b>Province:</b> $province</p>";
            echo "<p><b>Postal Code:</b> $postalCode</p>";
            echo "<p><b>Applied Program:</b> $course</p>";
    }
?>
</head>
</html>
</form>
</div>
</body>