# C++ Assignment

**Platformer με χρήση της βιβλιοθήκης SGG** 

### Γενικές Οδηγίες

- Καλή επαναχρησιμοποίηση κώδικα
- Ενιαίο και πολυμορφικό τρόπο κλήσης μεθόδων
- Αποδοτική εκμετάλλευση έτοιμων δομών της STL
- Ταχύτητα

## Requiremenets

- **Χρήση Δυναμικής Μνήμης**
    
    Οντότητες που έχουν μικρό χρόνο ζωής πρέπει να δημιουργούνται δναμικά στη μνήμη (με new) και να καταστρέφονται όταν δεν χρειάζονται.
    

- **Κληρονομικότητα και πολυμορφισμός**

    Σε λειτουργικό επίπεδο, διαθέτουμε οντότητες τύπου **“GameObject”** που κρατάνε και ενημερώνουν τη δική τους κατάσταση, και εξειδικευόμενες, παριστάνουν ένα είδος συγκεκριμένης λειτουργικής μονάδας του παιχνιδιού.

    - Αυτές τυπικά διαθέτουν κάποια μέθοδο “**draw**” και “**update**” που θα πρέπει να καλέσει η βασική λογική του παιχνιδιού μας σε ένα βρόγχο, όσο τρέχει. Από ένα GameObject, μπορώ να **εξειδικεύσω** οντότητες τύπου «παίχτης», «εχθρός», «εφέ», «πίστα» (level), «στατικό αντικείμενο» (περιβάλλοντος, background Κλπ.), “UI widget” κλπ. 
    
    - Στην εργασία σας καλείστε να οργανώσετε τις κλάσεις σας με έναν παρόμοιο ιεραρχικό τρόπο και να χρησιμοποιήσετε **πολυμορφισμό** για την κλήση μεθόδων στιγμιοτύπων αυτών των κλάσεων.

    
- **Χρήση βασική κλάσης GameObject, με τουλάχιστον τις μεθόδους που αναφέρονται.**
    - Η μέθοδος **update()** θα πρέπει να καλείται σε κάθε κύκλο ενημέρωσης της κατάστασης της εφαρμογής (βλ.οδηγίες της βιβλιοθήκης SGG).
    - Αντίστοιχα, η μέθοδος **draw()** καλείται για να σχεδιαστεί το στοιχείο.
    - Η μέθοδος **init()** είναι υπεύθυνη να αρχικοποιήσει ένα στιγμιότυπο, μετά από την κατασκευή του, ανχρειάζεται κάτι τέτοιο. Επίσης, μπορεί να κληθεί για να «ξανα-αρχικοποιήσει» ένα αντικείμενο του παιχνιδιού άμα κάνουμε κάποιο reset, επαναφέροντας την αρχική κατάστασή του, χωρίς να απαιτείται να ξαναδημιουργήσουμε το αντικείμενο.


- **Χρήση μοναδικής κλάσης GameState**
    - φυλάει δεδομένα για τη ροή και την κατάσταση του παιχνιδιού (π.χ. σε πιο level είμαστε, τα διαθέσιμα levels, στατιστικά, σκορ, κλπ.)
    - διαθέτει τις βασικές μεθόδους draw, init και update που καλούν τις αντίστοιχες έμμεσα ή άμεσα για οποιοδήποτε αντικείμενο λειτουργεί μέσα στο παιχνίδι σας.
    - είναι υπεύθυνη για το ξεκίνημα, την εναλλαγή επιπέδων (πιστών) και τον τερματισμό του παιχνιδιού.
    - παρέχει ένα κεντρικό σημείο πρόσβασης για να εντοπιστούν στοιχεία του παιχνιδιού (π.χ.
    GameState::getPlayer())
    

## Συλλογές

- Καλείστε να χρησιμοποιήσετε τις καταλληλότερες για τη δουλειά που τις χρειάζεστε συλλογές της STL για τις ανάγκες αποθήκευσης, αναζήτησης και μαζικής εκτέλεσης μεθόδων.
- **Προσοχή**: για να δουλέψουν ορισμένες από τις παρεχόμενες συλλογές σωστά με δικές σας κλάσεις, θα πρέπει να προσδιορίσετε τους κατάλληλους τελεστές για την ταξινόμηση ή το hashing των αντικειμένων (βλ. διαφάνειες μαθήματος).
- Συστήνεται αυστηρά να μην υλοποιήσετε δικές σας συλλογές για πράγματα που ήδη σας παρέχει η STL.
    
    

## Προαιρετικά Χαρακτηριστικά

- Σωστός σχεδιασμός και δόμηση κώδικα
- Σχολαστική δήλωση μεθόδων (πχ. σωστή χρήση **αναφορών** και **const** ορισμάτων ή μεθόδων)
- Εκμετάλλευση **templated** συναρτήσεων ή κλάσεων όπου φαίνεται χρήσιμο.
- Υπενθυμίζεται ότι ορισμένα μονοπάτια κώδικα που εκτελούν ενδεχομένως βαριές διαδικασίες υπολογισμών μπορούν να εκτελεστούν σε **ξεχωριστό(ά) thread(s)**
    - **MHN** το κάνετε για τη σχεδίαση ή οτιδήποτε έχει να κάνει με γραφικά και context παραθύρου, αυτά πρέπει να καλούνται από το κύριο thread της εφαρμογής. Αν έχετε πάρα πολλούς ελέγχους συγκρούσεων ή άλλους υπολογισμούς (π.χ. AI εχθρών), μπορείτε να τους εκτελέσετε παράλληλα με άλλες διαδικασίες.
- Μπορείτε να φτιάξετε **δυναμικό φόρτωμα πολλαπλών επιπέδων του παιχνιδιού**, καθώς αυτό εξελίσσεται, να φορτώνετε οποιονδήποτε αριθμό από επίπεδα αποθηκευμένα σε αρχεία στο δίσκο (όπως το demo που σας δίνεται).
- Μπορείτε να υλοποιήσετε σύστημα δημιουργίας και διαχείρισης συμβάντων που να
ελέγχονται από το GameState ή κάποιον κατανεμημένο μηχανισμό ανταλλαγής μηνυμάτων μεταξύ των οντοτήτων του παιχνιδιού.
    - Για παράδειγμα, στο demo παιχνίδι που σας έχει δοθεί, παράγονται συνεχώς
    σύντομα εξειδικευμένα αντικείμενα ως events με περιορισμένο χρόνο ζωής τα οποία διαχειρίζεται και ελέγχει (πότε ξεκινούν, πόσο διαρκούν, πώς καταστρέφονται) το κεντρικό αντικείμενο τύπου GameState (π.χ. εφέ μετάβασης επιπέδων, λεζάντες συγκομιδής πόντων, σύννεφα καπνού).

## Συγκρούσεις

Η διαδικασία ελέγχου γίνεται αρκετά απλά με μια συνάρτηση επικάλυψης μεταξύ παραλληλογράμμων (σας δίνεται).

## Oμάδες

- Σε περίπτωση που μια ομάδα επιλέξει να υλοποιήσει ένα αρκετά πιο σύνθετο παιχνίδι (μετά από συνεννόηση με το διδάσκοντα), τότε μπορεί να επεκταθεί μέχρι τα 3 μέλη.
- Η πολυπλοκότητα του παιχνιδιού, θα πρέπει να συνεπάγεται και αντίστοιχη πολυπλοκότητα στο σχεδιασμό του κώδικα και την υλοποίηση.
- Ενδεικτικά, μια τέτοια υλοποίηση θα πρέπει να περιλαμβάνει αρκετά από τα προαιρετικά στοιχεία που αναφέρονται στην ενότητα 2.3.
- Σε κάθε περίπτωση, όλα τα μέλη της ομάδας θα πρέπει να έχουν ασχοληθεί με κάποια λειτουργικότητα της εφαρμογής και να έχουν συντελέσει στη συγγραφή του κώδικα. Δηλαδή δεν επιτρέπεται να επιμεριστεί ο φόρτος μεταξύ των μελών ώστε κάποιος να επιμεληθεί μόνο των εικαστικών ή των ήχων.

## Οπτικοακουστικό Υλικό

- Δε βαθμολογήστε αρνητικά για την αισθητική της εφαρμογής.

## Βαθμολόγηση
![Untitled](https://github.com/fanisvl/platformer-game/assets/82032857/c8933ead-069f-4905-a7f4-2335fa8fc4bf)
![Untitled 1](https://github.com/fanisvl/platformer-game/assets/82032857/08b89e1f-f66e-4a59-aa1a-ece89e97cf44)


