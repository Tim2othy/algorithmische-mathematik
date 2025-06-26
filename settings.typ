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

  show math.equation: set text(font: "Cambria Math")


  set enum(
    full: true,
    numbering: (..num) => {
      let num = num.pos()
      numbering(if num.len() == 1 { "1." } else { "(a)" }, num.last())
    },
    spacing: 4em,
    indent: 1em,
  )

  set page(margin: (x: 1.5cm, y: 7em), numbering: "1", header: [
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
