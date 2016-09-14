'   Comments
'

Imports System
Imports System.Data
Imports System.Configuration
Imports System.Collections
Imports System.Web
Imports System.Web.Security
Imports System.Web.UI
Imports System.Web.UI.WebControls
Imports System.Web.UI.WebControls.WebParts
Imports System.Web.UI.HtmlControls

Public Class GV
    Public Shared RandomNumberInt As Integer
    Public Shared CurrentStakeAmountInt As Integer
End Class

Partial Class program4
    Inherits System.Web.UI.Page

    'Page_Load called whenever the page is loaded by user
    Function Page_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load
        Dim CurrentDateTime As String
        CurrentDateTime = DateTime.Now.ToString() ' "yyyy/MM/dd HH:mm:ss"
        PL_id.Text() = "Game started on: " + CurrentDateTime
    End Function

    'SubmitButtonClicked is called whenever the submit button is pressed. 
    'It is only called when the validators are passed
    Function SubmitButtonClicked(ByVal sender As Object, ByVal e As System.EventArgs)
        'Show Second half of the game.
        SecondHalfoftheCardGame.Visible = True
        'Show the current stake Text, update with current stake after the cookie search
        CurrentStakeAmount.Text = "Current stake: "

        Dim I As Integer
        Dim CookiewasFound As Boolean
        Dim NewStakeAmount As Integer

        CookiewasFound = False

        'Get current stake amount
        NewStakeAmount = stake.Text
        Dim CurrentNamePlaying As String
        'Get name playing as
        CurrentNamePlaying = name.Text

        'Loop through all cookies, if one cookies name matches with the name given go to the if statement
        For I = 0 To Request.Cookies.Count - 1
            If Request.Cookies.Item(I).Name = CurrentNamePlaying Then
                CookiewasFound = True
                'Get new stake amount, Add what was given and the previous cookie amount
                NewStakeAmount = NewStakeAmount + Request.Cookies.Item(I).Value
                'Update with stake amount
                CurrentStakeAmount.Text = CurrentStakeAmount.Text + NewStakeAmount.ToString

                'Update the cookie value and expiration
                Dim NewCookieToSave As HttpCookie = Request.Cookies.Item(I)
                NewCookieToSave.Value = NewStakeAmount.ToString
                NewCookieToSave.Expires = DateTime.Now.AddHours(24)
                HttpContext.Current.Response.Cookies.Set(NewCookieToSave)

                'Update the new stake amount
                GV.CurrentStakeAmountInt = NewStakeAmount
            End If
        Next

        'If no cookies were found
        If Not CookiewasFound Then
            'Create a new cookie with name, value and expiration date
            Dim NewCookieToMake As New HttpCookie(CurrentNamePlaying)
            NewCookieToMake.Value = NewStakeAmount
            NewCookieToMake.Expires = DateTime.Now.AddHours(24)
            Response.Cookies.Add(NewCookieToMake)

            'Add the new text with given stake and update the stake
            CurrentStakeAmount.Text = CurrentStakeAmount.Text + NewStakeAmount.ToString
            GV.CurrentStakeAmountInt = NewStakeAmount
        End If

        'Update the WageRange Max Value to whatever the current stake is, given or given+cookie
        WageRangeValidate.MaximumValue = GV.CurrentStakeAmountInt

    End Function

    'CardIsClicked is called whenever the card button is pressed
    'It is called and things are computed, if the card chosen wasn't A, a, F, f, 2-10 then display message and return changing nothing.
    'This is the validation for this part.
    Function CardIsClicked(ByVal sender As Object, ByVal e As System.EventArgs)

        Dim WonOrLostAmount As Integer
        Dim Bet As Integer
        Dim CardChosen As String

        'If User has hit Zero don't let them continue the game. Display Error
        If GV.CurrentStakeAmountInt <= 0 Then
            StakeHasHitZero.Visible = True
            StakeHasHitZero.Text = "Your stake is now zero (0). Please start a new game."
            Return 0
            'If they start a new game by pressing submit however, get rid of the error message and continue if stake is > 0
        Else
            StakeHasHitZero.Visible = False
        End If

        'Get Card Chosen, Bet/Wager Amount
        CardChosen = CardBox.Text
        Bet = WagerBox.Text
        Randomize()
        GV.RandomNumberInt = CInt(Int((52 * Rnd()) + 1))

        'Case Select for the card chosen. 
        'If they chose A or a and the RandomNumber matches, then give them winnings. Else take it away (-1)
        'If they chose F or f and the RandomNumber matches, then give them winnings. Else take it away (-1)
        'If they chose any of the numbers and the RandomNumber matches, then give them winnings. Else take it away (-1)
        '   All the numbers have independent winnings, 10 matches only 10's, 9 to 9, etc. Those are 
        Select Case CardChosen
            Case "A"
                If GV.RandomNumberInt = 1 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 2 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 3 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 4 Then
                    WonOrLostAmount = 12 * Bet
                Else
                    WonOrLostAmount = -1 * Bet
                End If
            Case "a"
                If GV.RandomNumberInt = 1 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 2 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 3 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 4 Then
                    WonOrLostAmount = 12 * Bet
                Else
                    WonOrLostAmount = -1 * Bet
                End If
            Case "F"
                If GV.RandomNumberInt = 5 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 6 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 7 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 8 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 9 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 10 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 11 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 12 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 13 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 14 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 15 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 16 Then
                    WonOrLostAmount = 3 * Bet
                Else
                    WonOrLostAmount = -1 * Bet
                End If
            Case "f"
                If GV.RandomNumberInt = 5 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 6 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 7 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 8 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 9 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 10 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 11 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 12 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 13 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 14 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 15 Then
                    WonOrLostAmount = 3 * Bet
                ElseIf GV.RandomNumberInt = 16 Then
                    WonOrLostAmount = 3 * Bet
                Else
                    WonOrLostAmount = -1 * Bet
                End If
            Case "10"
                If GV.RandomNumberInt = 17 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 18 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 19 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 20 Then
                    WonOrLostAmount = 12 * Bet
                Else
                    WonOrLostAmount = -1 * Bet
                End If
            Case "9"
                If GV.RandomNumberInt = 21 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 22 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 23 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 24 Then
                    WonOrLostAmount = 12 * Bet
                Else
                    WonOrLostAmount = -1 * Bet
                End If
            Case "8"
                If GV.RandomNumberInt = 25 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 26 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 27 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 28 Then
                    WonOrLostAmount = 12 * Bet
                Else
                    WonOrLostAmount = -1 * Bet
                End If
            Case "7"
                If GV.RandomNumberInt = 29 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 30 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 31 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 32 Then
                    WonOrLostAmount = 12 * Bet
                Else
                    WonOrLostAmount = -1 * Bet
                End If
            Case "6"
                If GV.RandomNumberInt = 33 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 34 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 35 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 36 Then
                    WonOrLostAmount = 12 * Bet
                Else
                    WonOrLostAmount = -1 * Bet
                End If
            Case "5"
                If GV.RandomNumberInt = 37 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 38 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 39 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 40 Then
                    WonOrLostAmount = 12 * Bet
                Else
                    WonOrLostAmount = -1 * Bet
                End If
            Case "4"
                If GV.RandomNumberInt = 41 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 42 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 43 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 44 Then
                    WonOrLostAmount = 12 * Bet
                Else
                    WonOrLostAmount = -1 * Bet
                End If
            Case "3"
                If GV.RandomNumberInt = 45 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 46 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 47 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 48 Then
                    WonOrLostAmount = 12 * Bet
                Else
                    WonOrLostAmount = -1 * Bet
                End If
            Case "2"
                If GV.RandomNumberInt = 49 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 50 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 51 Then
                    WonOrLostAmount = 12 * Bet
                ElseIf GV.RandomNumberInt = 52 Then
                    WonOrLostAmount = 12 * Bet
                Else
                    WonOrLostAmount = -1 * Bet
                End If
            Case Else
                'Validation here.
                InCorrectCardBox.Text = "Please enter A, a, F, f, or 2-10"
                Return 0
        End Select

        'Display Card Image of winning card
        CardButton.ImageUrl = "~/Images/" + GV.RandomNumberInt.ToString + ".png"
        'Update with winnings or losings
        GV.CurrentStakeAmountInt = GV.CurrentStakeAmountInt + WonOrLostAmount
        'Display current stake, with updated winnings or losings
        CurrentStakeAmount.Text = "Current stake: " + GV.CurrentStakeAmountInt.ToString

        'Display amount they won or lost. 
        WonLostLabel.Text = "Won/Lost: " + WonOrLostAmount.ToString
        'Make sure the second half stays visible
        SecondHalfoftheCardGame.Visible = True

        Dim CurrentNamePlaying As String
        CurrentNamePlaying = name.Text
        'Updated cookie/make a new cookie. with current stake amount
        For I = 0 To Request.Cookies.Count - 1
            If Request.Cookies.Item(I).Name = CurrentNamePlaying Then
                Dim NewCookieToSave As HttpCookie = Request.Cookies.Item(I)
                NewCookieToSave.Value = GV.CurrentStakeAmountInt.ToString
                NewCookieToSave.Expires = DateTime.Now.AddHours(24)
                HttpContext.Current.Response.Cookies.Set(NewCookieToSave)
            End If
        Next
    End Function

End Class
