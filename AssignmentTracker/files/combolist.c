#include<gtk/gtk.h>
//For Semester List.
static void semesterList(GtkWidget *combo){
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Semester I");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Semester II");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Semester III");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Semester IV");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Semester V");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Semester VI");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Semester VII");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Semester VIII");
}

//For courses.
static void SemesterI(GtkWidget *combo){
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Engineering Mathematics");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Computer Programming");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Engineering Drawing I");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Engineering Physics");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Applied Mechanics");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Basic Electrical Engineering");
}
static void SemesterII(GtkWidget *combo){
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Engineering Mathematics II");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Engineering Drawing II");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Basic Electronics Engineering");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Engineering Chemistry");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Fundamental of Thermodynamics  & Heat Transfer");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Workshop Technology");
}
static void SemesterIII(GtkWidget *combo){
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Engineering Mathematics III");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Object Oriented Programming");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Electrical Circuit Theory");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Theory of Computation");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Electronics Devices and Circuit");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Digital Logic");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Electromagnetism");
}
static void SemesterIV(GtkWidget *combo){
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Electrical Machine");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Numerical Method");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Applied Mathematics");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Instrumentation I");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Data Structure and Algorithm");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Microprocessor");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Discrete Structure");
}
static void SemesterV(GtkWidget *combo){
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Communication English");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Probability and Statistics");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Computer Organization and Architecture");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Software Engineering");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Computer Graphic");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Instrumentation II");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Data Communation");
}
static void SemesterVI(GtkWidget *combo){
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Engineering Economics");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Object Oriented Analysis and Design");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Artificial Intelligence");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Operating System");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Embedded System");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Database Management System");
}
static void SemesterVII(GtkWidget *combo){
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "ICT Project Management");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Organization and Management");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Energy Environment and Society");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Distributed System");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Electronics Devices and Circuit");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Computer Networks and Security");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Digital Signal Analysis and Processing");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Elective I");
}
static void SemesterVIII(GtkWidget *combo){
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Engineering Professional Practice");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Information System");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Internet and Intranet");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Simulation and Modeling");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Elective II");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Elective III");
}