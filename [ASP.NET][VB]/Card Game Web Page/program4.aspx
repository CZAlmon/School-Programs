<%@ Page Language="VB" AutoEventWireup="false" CodeFile="program4.aspx.vb" Inherits="program4" Debug="True" %>
 
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional// EN" "http://www.w3.org/TR/chtml1/DTD/xhtml1-transitional.dtd>
 
<html xmlns="http://www.w3.org/1999/xhtml">

<head id="Head1" runat="server">
    <title>Pick a Card by Zach Almon</title>
</head>
    <style> 
        body {
            background: url("Images/background.jpg");
            background-size: cover;
        }
        h1 {
            color: white;
        }
        p {
            color: white;
        }
</style>
    <!-- Comments -->
<body>
    <form id="Form1" runat="server">
        <h1>Pick a Card</h1>

        <br />
        <!-- Upon loading of the page, display current time game started on -->
        <h3><asp:Label ID="PL_id" ForeColor="White" runat="server" Text=""></asp:Label></h3>

        <br />
        <!-- Name label and input box -->
        <p>Name: </p>
        <asp:TextBox Width="200" ID="name" runat="server"></asp:TextBox>
        <!-- Validate name is not blank, nothing more. -->
        <asp:RequiredFieldValidator Font-Bold="true" ForeColor="Red" ControlToValidate="name" ID="notblankname" runat="server" ErrorMessage="Please enter your name"></asp:RequiredFieldValidator>

        <br />
        <!-- Stake label and input box -->
        <p>Stake: </p>
        <asp:TextBox  Width="200"  ID="stake" runat="server"></asp:TextBox>
        <!-- Validate stake box is not blank -->
        <asp:RequiredFieldValidator  Font-Bold="true" ForeColor="Red" ControlToValidate="stake" ID="notblankstake" runat="server" ErrorMessage="Stake must be an integer Between 0 and 1000"></asp:RequiredFieldValidator>
        <!-- Validate stake box within range min value (0) and Max value (set in VB File) -->
        <asp:RangeValidator ID="rangevalidatorstake" Font-Bold="true" ForeColor="Red" MinimumValue="0" ControlToValidate="stake" MaximumValue="1000" Type="Integer" runat="server" ErrorMessage="Stake must be an integer Between 0 and 1000"></asp:RangeValidator>

        <br />
        <br />
        <!-- Submit button, onclick only when validates are passed -->
        <asp:Button ID="Button1" runat="server" Text="Submit" OnClick="SubmitButtonClicked"></asp:Button>

        <!-- Second half of game, hidden until submit is pressed -->
        <asp:ScriptManager ID="ScriptManager1" runat="server"></asp:ScriptManager>
        <asp:UpdatePanel ID="SecondHalfoftheCardGame" runat="server"  Visible="false">
            <ContentTemplate>

                <br />
                <br />
                <br />
                <!-- Current Stake label, updated by submit and card click functions -->
                <!-- displays current stake +- winnings or losings (plus cookies if they exist) -->
                <!-- Cookies are set to expire after 24 hours, therefore no need to check if ones exist before then -->
                <asp:Label ID="CurrentStakeAmount" ForeColor="White" Font-Bold="true" runat="server" Text="Current stake: "></asp:Label>
                <asp:Label ID="StakeHasHitZero" Font-Bold="true" ForeColor="Red" runat="server" Text="" Visible="false"></asp:Label>

                <br />
                <!-- Wager Label and input box -->
                <asp:Label ID="WagerLabel" ForeColor="White" Font-Bold="true" runat="server" Text="Wager: "></asp:Label>
                <asp:TextBox ID="WagerBox" AutoPostBack="true" runat="server" Width="200"></asp:TextBox>
                <!-- Validate Wage box is not empty -->
                <asp:RequiredFieldValidator Font-Bold="true" ForeColor="Red" ID="wagervalidator" ControlToValidate="WagerBox" runat="server" ErrorMessage="Bet must be an integer <= current stake and >= 0"></asp:RequiredFieldValidator>
                <!-- Validate Wage box within range min value (0) and Max value (set in VB File) -->
                <asp:RangeValidator ID="WageRangeValidate" Font-Bold="true" ForeColor="Red" MinimumValue="0" ControlToValidate="WagerBox" runat="server" Type="Integer" ErrorMessage="Bet must be an integer <= current stake and >= 0"></asp:RangeValidator>
                
                <br />
                <!-- Simple label, with instructions -->
                <p>Select card (A or a for ace, F or f for face card or 2-10)</p>
                
                <br />
                <!-- Second Insturctions Label with Cardbox input box -->
                <p>Then click on the card image:</p>
                <asp:TextBox ID="CardBox" runat="server" Width="200"></asp:TextBox>

                <!-- If validation not passed in VB file update this label which will be right after CardBox input box -->
                <asp:Label ID="InCorrectCardBox" Font-Bold="true" ForeColor="Red" runat="server" Text=""></asp:Label>
                
                <br />
                <!-- Won lost label. Updated in VB file with "Won/Lost: " + Amount won or lost when playing -->
                <!-- If validation not passed, does not change. Cardbox Validation must be passed. -->
                <asp:Label ID="WonLostLabel" runat="server" ForeColor="White" Text="Won/lost: " Font-Bold="true"></asp:Label>
                
                <br />
                <!-- Clickable Card image button. Validate Cardbox Input in VB File. -->
                <!-- If validation not passed, see above -->
                <asp:ImageButton ID="CardButton" ImageUrl="Images/b1fv.png" OnClick="CardIsClicked" runat="server" />
            </ContentTemplate>
        </asp:UpdatePanel>
    </form>
</body>
</html>
