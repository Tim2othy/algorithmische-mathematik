#let project(
  course: "",
  exersise: "",
  body,
) = {
  // Set the document's basic properties.
  set text(
    font: "New Computer Modern",
    size: 12pt,
    lang: "de",
  )

  show link: underline
  set list(indent: 1em)

  set enum(
    numbering: "1.a.",
    spacing: 1.2em,
    indent: 1em,
  )

  set page(margin: (x: 1.5cm, y: 7em), header: [
    #course   #h(1fr)     #exersise\
  ])

  // Title row.
  align(center)[
    #text(1.33em)[
      #v(1em)
      #course
      #v(1em)
      #exersise
      #v(1.5em)
    ]
  ]

  // Main body.
  set par(justify: true)

  body
}
