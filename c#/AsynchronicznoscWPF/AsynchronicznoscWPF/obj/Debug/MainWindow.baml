   M S B A M L   `   `   `  ����N  JAsynchronicznoscWPF, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null9!clr-namespace:AsynchronicznoscWPFAsynchronicznoscWPF  5   	   $    AsynchronicznoscWPF.MainWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   3local!clr-namespace:AsynchronicznoscWPF     5   	     � Title$  
MainWindow��5   	   $	��350��6   $	��300��6)   .��5	      �  � RowDefinitions 5
   
   �� 5      $
��Auto �6   �� 5      $
��Auto �6   �� 5      $
��Auto �6   �� 5      $
��Auto �6   �� 5      $
��Auto �6   �� 5      $
��Auto �6   �� 5      $
��Auto �6   �� 5      $��* �6   �� 5      $
��Auto �6   .+�5   
   �� -   5         ��Name$ Etykieta��5      $
��Wrap=�6&   $"��Oczekiwanie na operację ...��5      $��Center=�5      $��5q�5      $��20(�6   �� 5   
   -   5         ��Name$ 	ButSynchr��5      $��Wywołanie synchroniczne��6$   $��1��6F   $��5q�6S   6^   �� 5   
   -   5        $ ButNowyWatek��5      $!��Uruchomienie w nowym wątku��6'   $��2��5      $��5q�6   6)   �� 5   
   -   5        $ ButMessageBox��5      $,��&Uruchomienie MessageBox w nowym wątku��5      $��3��6A   $��5q�5      6   �� 5   
   -   5        $ 
ButDispAll��5      $-��'Uruchomienie wszystkiego w dispatcherze��5       $��4��6C   $��5q�5!      6   �� 5"   
   -   5        $ ButDispUpdate��5"      $.��(Uruchomienie aktualizacji w dispatcherze��5#      $��5��6D   $��5q�5$      6   �� 5%   
   -   5        $ ButAsync��5%      $��Uruchomienie async-await��5&      $��6��64   $��5q�5'      6   �� 5(   
   $��8��6    �� Orientation$ 
Horizontal=�6"   $��5q�6;   .+�5)      �� $��23��6   $	��180��6"    �� TextWrapping$
 Wrap=�6.   $��TextBox��6B   �� 5*      $��CheckBox��6   $��5q�6*   5+      5-      5.      